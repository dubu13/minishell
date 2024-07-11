/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 05:02:18 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/10 22:11:21 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void execute_child_process(int pipefd[2], t_tree *tree, t_mini *mini)
{
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	// close(pipefd[0]);
	// close(pipefd[1]);
	exec_node(tree->left, mini);
	exit(EXIT_SUCCESS);
}

static void execute_parent_process(int pipefd[2], pid_t pid, t_tree *tree, t_mini *mini)
{
	if (dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	// close(pipefd[0]);
	// close(pipefd[1]);
	exec_node(tree->right, mini);
	if (waitpid(pid, NULL, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

void exec_pipe(t_tree *tree, t_mini *mini)
{
	int pipefd[2];
	pid_t pid;
	int fd_temp;

	fd_temp = dup(STDIN_FILENO);
	if (fd_temp == -1)
	{
		perror("dup");
		exit(EXIT_FAILURE);
	}

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		execute_child_process(pipefd, tree, mini);
	}
	else
	{
		close(pipefd[1]);
		execute_parent_process(pipefd, pid, tree, mini);
	}

	if (dup2(fd_temp, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd_temp);
		exit(EXIT_FAILURE);
	}
	close(fd_temp);
}
