/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:44:42 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/10 22:03:12 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

void	read_heredoc(t_tree *tree, int fd[2])
{
	char	*read;

	while (1)
	{
		write(1, "> ", 2);
		read = get_next_line(STDIN_FILENO);
		if (ft_strncmp(read, tree->limit, ft_strlen(tree->limit)) == 0)
		{
			free(read);
			break ;
		}
		write(fd[1], read, ft_strlen(read));
		free(read);
		read = NULL;
	}
}

void	heredoc(t_tree *tree, t_mini *mini)
{
	int		fd[2];
	int		fd_temp;

	fd_temp = dup(STDIN_FILENO);
	if (pipe(fd) == -1)
		perror("pipe");
	read_heredoc(tree, fd);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("dup2");
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		perror("close");
	tree->limit = NULL;
	exec_node(tree, mini);
	if (dup2(fd_temp, STDIN_FILENO) == -1)
		perror("dup2");
	close(fd_temp);
}

void	append_rdirect(t_tree *tree, t_mini *mini)
{
	int		fd_out;
	int		fd_temp;
	char	**out_files;

	out_files = tree->append;
	fd_temp = dup(STDOUT_FILENO);
	while (*out_files)
	{
		fd_out = open(*out_files, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_out < 0 && access(*out_files, F_OK) < 0)
			perror("minishell : <file> No such file or directory");
		else
		{
			if (dup2(fd_out, STDOUT_FILENO) < 0)
				perror("dup2");
			close(fd_out);
		}
		out_files++;
	}
	tree->append = NULL;
	exec_node(tree->right, mini);
	if (dup2(fd_temp, STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd_temp);
}

void	out_rdirect(t_tree *tree, t_mini *mini)
{
	int		fd_out;
	int		fd_temp;
	char	**out_files;

	out_files = tree->out;
	fd_temp = dup(STDOUT_FILENO);
	while (*out_files)
	{
		fd_out = open(*out_files, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_out < 0 && access(*out_files, F_OK) < 0)
			perror("minishell : <file> No such file or directory");
		else
		{
			if (dup2(fd_out, STDOUT_FILENO) < 0)
				perror("dup2");
			close(fd_out);
		}
		out_files++;
	}
	tree->out = NULL;
	exec_node(tree, mini);
	if (dup2(fd_temp, STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd_temp);
}

void	in_rdirect(t_tree *tree, t_mini *mini)
{
	int	fd_in;
	int	fd_temp;

	fd_in = open(tree->in, O_RDONLY);
	if (fd_in < 0)
	{
		if (access(tree->in, F_OK) < 0)
			perror("minishell : <file> No such file or directory");
		else
			perror("open");
	}
	fd_temp = dup(STDIN_FILENO);
	if (dup2(fd_in, STDIN_FILENO) < 0)
		perror("dup2");
	tree->in = NULL;
	exec_node(tree, mini);
	if (dup2(fd_temp, STDIN_FILENO) < 0)
		perror("dup2");
	close(fd_in);
	close(fd_temp);
}
