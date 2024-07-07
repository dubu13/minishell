/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:14:50 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/07 03:03:45 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
exit status :
0 = success
1 = general errors
2 = misuse of shell builtins
126 = command invoked cannot execute
127 = command not found
128 = invalid argument to exit (non numeric)
130 = terminated by ctrl-c
128 + signal number = terminated by signal

*/

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
	else
		exec_command(tree->cmd, mini);
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
	else
	{
		ft_putendl_fd("UNSUPPORTED TOKEN TYPE!", 2);
		exit(1);
	}
}

void	exec_pipe(t_tree *tree, t_mini *mini)
{
	int pipefd[2];
	pid_t pid;
	int fd_temp;

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
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2");
			close(pipefd[1]);
			exit(EXIT_FAILURE);
		}
		close(pipefd[1]);
		exec_tree(tree->left, mini);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pipefd[1]);
		if (dup2(pipefd[0], STDIN_FILENO) == -1)
		{
			perror("dup2");
			close(pipefd[0]);
			exit(EXIT_FAILURE);
		}
		close(pipefd[0]);
		exec_tree(tree->right, mini);
		if (waitpid(pid, NULL, 0) == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}
	if (dup2(fd_temp, STDIN_FILENO) < 0)
		perror("dup2");
	close(fd_temp);
}