/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:02:18 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/10 18:12:23 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	execute_child_process(int pipefd[2], t_tree *tree, t_mini *mini)
{
	close(pipefd[0]);
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	close(pipefd[1]);
	exec_node(tree->left, mini);
	exit(EXIT_SUCCESS);
}

static void	execute_parent_process(int pipefd[2], pid_t pid, t_tree *tree,
		t_mini *mini)
{
	close(pipefd[1]);
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	if (tree->right)
		exec_node(tree->right, mini);
	else
		exec_node(tree, mini);
	if (waitpid(pid, NULL, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

void	exec_pipe(t_tree *tree, t_mini *mini)
{
	int		pipefd[2];
	pid_t	pid;
	int		fd_temp;

	fd_temp = dup(STDIN_FILENO);
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		execute_child_process(pipefd, tree, mini);
	else
		execute_parent_process(pipefd, pid, tree, mini);
	if (dup2(fd_temp, STDIN_FILENO) < 0)
		perror("dup2");
	close(fd_temp);
}
