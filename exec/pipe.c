/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:02:18 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/18 15:11:22 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	execute_child_process(int pipefd[2], t_tree *tree, t_mini *mini)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		close_and_exit(pipefd, "dup2", mini, "1");
	exec_node(tree->left, mini);
	free_and_exit(NULL, mini, "1");
}

static void	execute_parent_process(int pipefd[2], pid_t pid, \
	t_tree *tree, t_mini *mini)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		close_and_exit(pipefd, "dup2", mini, "1");
	close(pipefd[1]);
	exec_node(tree->right, mini);
	close(pipefd[0]);
	if (waitpid(pid, NULL, 0) == -1)
		free_and_exit("waitpid", mini, "1");
}

void	create_output_files(t_tree *node, t_mini *mini)
{
	int	fd_out;
	int	fd_temp;

	if (!node)
		return ;
	fd_temp = dup(STDOUT_FILENO);
	if (node->out)
	{
		char **out_files = node->out;
		while (*out_files)
		{
			fd_out = open(*out_files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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
	if (node->append)
	{
		char **out_files = node->append;
		while (*out_files)
		{
			fd_out = open(*out_files, O_WRONLY | O_CREAT | O_APPEND, 0644);
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
	create_output_files(node->left, mini);
	create_output_files(node->right, mini);
	if (dup2(fd_temp, STDOUT_FILENO) < 0)
		free_and_exit("minishell: error in dup2", mini, "1");
	close(fd_temp);
}

void	exec_pipe(t_tree *tree, t_mini *mini)
{
	int		pipefd[2];
	pid_t	pid;
	int		fd_temp;

    create_output_files(tree, mini);
	fd_temp = dup(STDIN_FILENO);
	if (fd_temp == -1)
		free_and_exit("dup", mini, "1");
	if (pipe(pipefd) == -1)
		free_and_exit("pipe", mini, "1");
	pid = fork();
	if (pid == -1)
		close_and_exit(pipefd, "fork", mini, "1");
	else if (pid == 0)
		execute_child_process(pipefd, tree, mini);
	else
		execute_parent_process(pipefd, pid, tree, mini);
	if (dup2(fd_temp, STDIN_FILENO) == -1)
	{
		close(fd_temp);
		free_and_exit("dup2", mini, "1");
	}
	close(fd_temp);
}
