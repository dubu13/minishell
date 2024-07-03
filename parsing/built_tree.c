/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:12:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/03 19:03:40 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree *create_node(t_token *token)
{
    t_tree *node = malloc(sizeof(t_tree));
    if (!node)
        return (NULL);
    node->type = token->type;
    node->left = NULL;
    node->right = NULL;
    if (token->type == CMD)
	{
        int i = 0;
        t_token *current_token = token;
        while (current_token && current_token->type != PIPE)
		{
            i++;
            current_token = current_token->next;
        }
        node->cmd = malloc(sizeof(char *) * (i + 1));
        if (!node->cmd) {
            free(node);
            return (NULL);
        }
        i = 0;
        current_token = token;
        while (current_token && current_token->type != PIPE)
		{
            node->cmd[i++] = ft_strdup(current_token->value);
            current_token = current_token->next;
        }
        node->cmd[i] = NULL;
    }
	else 
        node->cmd = NULL;
    return node;
}

t_tree *build_tree(t_token **tokens)
{
    if (!*tokens)
        return (NULL);
    t_tree *root = NULL, *current = NULL;
    t_token *token = *tokens;
    while (token)
	{
        if (token->type == CMD || token->type == PIPE)
		{
            t_tree *new_node = create_node(token);
            if (!root)
                root = new_node;
			else if (current->type == PIPE)
                current->right = new_node;
            else
			{
                t_tree *pipe_node = malloc(sizeof(t_tree));
                if (!pipe_node)
                    return (NULL);
                pipe_node->type = PIPE;
                pipe_node->left = root;
                pipe_node->right = new_node;
                root = pipe_node;
            }
            current = new_node;
        }
        token = token->next;
    }
    return root;
}
/*
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
*/

/*void	execute_tree(t_tree *node, t_mini *mini)
{
	if (!node)
		return ;
	execute_tree(node->left, mini);
	if (node->right)
		execute_pipe(node, mini);
	else
		execute_command(node, mini);
	execute_tree(node->right, mini);
}*/
