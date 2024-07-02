/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:12:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/02 18:02:32 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*create_node(t_token *token)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = token->type;
	node->cmd = token->value;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Function to append a string to the cmd array
char	**append_cmd(char **cmd, char *value)
{
	int		i;
	char	**new_cmd;

	// Count the number of strings in cmd
	i = 0;
	while (cmd[i])
		i++;

	// Allocate memory for new_cmd
	new_cmd = (char**)ft_calloc(i + 2, sizeof(char*));
	if (!new_cmd)
		return (NULL);

	// Copy the strings from cmd to new_cmd
	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = cmd[i];
		i++;
	}

	// Add the new value to new_cmd
	new_cmd[i] = ft_strdup(value);
	new_cmd[i + 1] = NULL;

	// Free the old cmd
	free(cmd);

	return (new_cmd);
}

// Modify the build_tree function
t_tree	*build_tree(t_token **tokens)
{
	t_tree	*node;
	t_tree	*cmd_node;
	t_tree	*arg_node;

	node = NULL;
	if (!*tokens)
		return (NULL);
	cmd_node = create_node(*tokens);
	*tokens = (*tokens)->next;
	while (*tokens && (*tokens)->type != PIPE)
	{
		cmd_node->cmd = append_cmd(cmd_node->cmd, (*tokens)->value); // Append the value from token to cmd
		if (!cmd_node->cmd)
		{
			return (NULL);
		}
		*tokens = (*tokens)->next;
	}
	if (*tokens && (*tokens)->type == PIPE)
	{
		node = create_node(*tokens);
		*tokens = (*tokens)->next;
		node->left = cmd_node;
		node->right = build_tree(tokens);
	}
	else
	{
		node = cmd_node;
	}
	return (node);
}

void	execute_command(t_tree *node, t_mini *mini)
{
	char	command[1024];

	if (node == NULL)
		return ;
	if (check_builtin(node->cmd))
	{
		exec_builtin(mini);
	}
	else
	{
		ft_strlcpy(command, node->cmd, sizeof(command));
		if (node->left)
		{
			ft_strlcat(command, " ", sizeof(command));
			ft_strlcat(command, node->left->cmd, sizeof(command));
		}
		external_command(command, mini);
	}
}

void	left_pipe(pid_t pid_left, int fd[2], t_tree *node, t_mini *mini)
{
	if (pid_left == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid_left == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}
		execute_command(node->left, mini);
		exit(EXIT_SUCCESS);
	}
}

void	right_pipe(pid_t pid_right, int fd[2], t_tree *node, t_mini *mini)
{
	if (pid_right == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid_right == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
		{
			perror("close");
			exit(EXIT_FAILURE);
		}
		execute_command(node->right, mini);
		exit(EXIT_SUCCESS);
	}
}

void	execute_pipe(t_tree *node, t_mini *mini)
{
	int		fd[2];
	pid_t	pid_left;
	pid_t	pid_right;

	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid_left = fork();
	if (pid_left == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		close(fd[1]);
		execute_command(node->left, mini);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	pid_right = fork();
	if (pid_right == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			exit(EXIT_FAILURE);
		}
		close(fd[0]);
		execute_command(node->right, mini);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	waitpid(pid_right, NULL, 0);
	waitpid(pid_left, NULL, 0);
}

void	execute_tree(t_tree *node, t_mini *mini)
{
	if (!node)
		return ;
	execute_tree(node->left, mini);
	if (node->right)
	{
		execute_pipe(node, mini);
	}
	else
	{
		execute_command(node, mini);
	}
	execute_tree(node->right, mini);
}
