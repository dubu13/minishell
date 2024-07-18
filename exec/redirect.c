/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:44:42 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/17 14:09:29 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	read_heredoc(t_tree *tree, int fd[2], t_mini *mini, t_token *token)
{
	char	*read;
	char	*expanded;
	char	*temp;

	while (1)
	{
		read = readline("> ");
		if (!read || !ft_strncmp(read, tree->limit, ft_strlen(tree->limit) + 1))
		{
			free(read);
			break ;
		}
		temp = read;
		expanded = ft_strdup("");
		while (*temp)
			expanded = expander(&temp, expanded, mini, token);
		if (expanded)
		{
			write(fd[1], expanded, ft_strlen(expanded));
			free(expanded);
		}
		write(fd[1], "\n", 1);
		free(read);
	}
}

void	heredoc(t_tree *tree, t_mini *mini)
{
	int		fd[2];
	int		fd_temp;

	fd_temp = dup(STDIN_FILENO);
	if (pipe(fd) == -1)
		free_and_exit("error in pipe", mini, "1");
	read_heredoc(tree, fd, mini, mini->token_list);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		free_and_exit("error in dup2", mini, "1");
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		free_and_exit("error in close", mini, "1");
	free(tree->limit);
	tree->limit = NULL;
	exec_node(tree, mini);
	if (dup2(fd_temp, STDIN_FILENO) == -1)
		free_and_exit("error in dup2", mini, "1");
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
			msg_for_rdir(*tree->append, mini, 1);
		else
		{
			if (dup2(fd_out, STDOUT_FILENO) < 0)
				free_and_exit("error in dup2", mini, "1");
			close(fd_out);
		}
		out_files++;
	}
	free_array(tree->append);
	tree->append = NULL;
	exec_node(tree, mini);
	if (dup2(fd_temp, STDOUT_FILENO) < 0)
		free_and_exit("error in dup2", mini, "1");
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
			msg_for_rdir(*tree->out, mini, 1);
		else
		{
			if (dup2(fd_out, STDOUT_FILENO) < 0)
				free_and_exit("minishell: error in dup2", mini, "1");
			close(fd_out);
		}
		out_files++;
	}
	free_array(tree->out);
	tree->out = NULL;
	exec_node(tree, mini);
	if (dup2(fd_temp, STDOUT_FILENO) < 0)
		free_and_exit("minishell: error in dup2", mini, "1");
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
			msg_for_rdir(tree->in, mini, 1);
		else
			free_and_exit("minishell: error in open", mini, "1");
	}
	fd_temp = dup(STDIN_FILENO);
	if (fd_in > 0 && dup2(fd_in, STDIN_FILENO) < 0)
		free_and_exit("minishell: error in dup2", mini, "1");
	close(fd_in);
	free(tree->in);
	tree->in = NULL;
	exec_node(tree, mini);
	if (dup2(fd_temp, STDIN_FILENO) < 0)
		free_and_exit("minishell: error in dup2", mini, "1");
	close(fd_temp);
}
