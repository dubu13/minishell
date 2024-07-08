/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:14:50 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/07 16:37:09 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_exec(t_mini *mini)
{
	t_tree	*tree;

	if (!mini->binary_tree)
		return ;
	tree = mini->binary_tree;
	if (tree->type == PIPE)
		exec_pipe(tree, mini);
	else if (tree->in)
		in_rdirect(tree, mini);
	else if (tree->out)
		out_rdirect(tree, mini);
	else if (tree->append)
		append_rdirect(tree, mini);
	else if (tree->limit)
		heredoc(tree, mini);
	else
		exec_tree(tree, mini);
}

void	exec_command(char **cmd, t_mini *mini)
{
	if (check_builtin(cmd[0]))
		exec_builtin(cmd, mini);
	else
		external_command(cmd, mini);
}

void	exec_tree(t_tree *node, t_mini *mini)
{
	if (!node)
		return ;
	if (node->type == CMD)
		exec_command(node->cmd, mini);
	else if (node->type == PIPE)
		exec_pipe(node, mini);
	else if (node->in)
		in_rdirect(node, mini);
	else if (node->out)
		out_rdirect(node, mini);
	else if (node->append)
		append_rdirect(node, mini);
	else if (node->limit)
		heredoc(node, mini);
}
