/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:12:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/03 16:38:45 by dkremer          ###   ########.fr       */
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
	node->cmd = append_cmd(node->cmd, token->value);
	node->left = NULL;
	node->right = NULL;
	return (node);
}

char	**append_cmd(char **cmd, char *value)
{
	int		i;
	char	**new_cmd;

	i = 0;
	while (cmd[i])
		i++;
	new_cmd = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!new_cmd)
		return (NULL);
	i = 0;
	while (cmd[i])
	{
		new_cmd[i] = cmd[i];
		i++;
	}
	new_cmd[i] = ft_strdup(value);
	new_cmd[i + 1] = NULL;
	free(cmd);
	return (new_cmd);
}

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
		cmd_node->cmd = append_cmd(cmd_node->cmd, (*tokens)->value);
		if (!cmd_node->cmd)
			return (NULL);
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
		node = cmd_node;
	return (node);
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
		execute_pipe(node, mini);
	else
		execute_command(node, mini);
	execute_tree(node->right, mini);
}
