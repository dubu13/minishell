/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:14:50 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/10 18:19:24 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_cmd(t_tree *tree, t_mini *mini)
{
	int	builtin;

	builtin = check_builtin(tree->cmd[0]);
	if (builtin == 0)
		exec_builtin(tree->cmd, mini);
	external_command(tree->cmd, mini);
}

void	exec_node(t_tree *node, t_mini *mini)
{
	if (node->type == PIPE)
		exec_pipe(node, mini);
	else if (node->type == RDIR_IN)
		in_rdirect(node, mini);
	else if (node->type == RDIR_OUT)
		out_rdirect(node, mini);
	else if (node->type == RDIR_APPEND)
		append_rdirect(node, mini);
	else if (node->type == RDIR_HEREDOC)
		heredoc(node, mini);
	else if (node->type == CMD)
		exec_cmd(node, mini);
}

int	exec_command(t_tree *node, t_mini *mini)
{
	pid_t	pid;
	int		wpidstatus;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (EXIT_FAILURE);
	}
	if (pid == 0)
	{
		exec_node(node, mini);
		exit (EXIT_FAILURE);
	}
	waitpid(pid, &wpidstatus, 0);
	return (EXIT_SUCCESS);
}
