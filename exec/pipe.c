/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:02:18 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/19 20:22:57 by dhasan           ###   ########.fr       */
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
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		free_and_exit("waitpid", mini, "1");
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		close_and_exit(pipefd, "dup2", mini, "1");
	close(pipefd[1]);
	exec_node(tree->right, mini);
	close(pipefd[0]);
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
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
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
