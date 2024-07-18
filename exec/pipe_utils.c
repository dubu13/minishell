/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:52:21 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/18 21:55:08 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_out_files(t_tree *node, t_mini *mini)
{
	char	**out_files;
	int		fd_out;

	out_files = node->out;
	while (*out_files)
	{
		fd_out = open(*out_files, O_CREAT, 0644);
		if (fd_out < 0 && access(*out_files, F_OK) < 0)
			msg_for_rdir(*node->out, mini, 1);
		else
		{
			if (dup2(fd_out, STDOUT_FILENO) < 0)
				free_and_exit("minishell: error in dup2", mini, "1");
			close(fd_out);
		}
		out_files++;
	}
}

void	create_append_files(t_tree *node, t_mini *mini)
{
	char	**out_files;
	int		fd_out;

	out_files = node->append;
	while (*out_files)
	{
		fd_out = open(*out_files, O_CREAT, 0644);
		if (fd_out < 0 && access(*out_files, F_OK) < 0)
			msg_for_rdir(*node->append, mini, 1);
		else
		{
			if (dup2(fd_out, STDOUT_FILENO) < 0)
				free_and_exit("error in dup2", mini, "1");
			close(fd_out);
		}
		out_files++;
	}
}

void	create_output_files(t_tree *node, t_mini *mini)
{
	int		fd_temp;

	if (!node)
		return ;
	fd_temp = dup(STDOUT_FILENO);
	if (node->out)
		create_out_files(node, mini);
	if (node->append)
		create_append_files(node, mini);
	create_output_files(node->left, mini);
	create_output_files(node->right, mini);
	if (dup2(fd_temp, STDOUT_FILENO) < 0)
		free_and_exit("minishell: error in dup2", mini, "1");
	close(fd_temp);
}
