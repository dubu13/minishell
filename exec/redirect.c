/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:44:42 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/07 03:07:41 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* NOTE
echo < test
Input Redirection (<): The shell opens the file test and associates it with standard input (stdin).
echo Command: The echo command does not read from stdin; it only prints its arguments.
No Arguments: Since no arguments are provided to echo, it just outputs a newline character.
---------
cat < test
Input Redirection (<): The shell opens the file test and associates it with standard input (stdin).
cat Command: The cat command reads from stdin when no file is specified.
Output: The cat command reads the contents of test and outputs it to stdout.
*/

// void	exec_rdirect()
// {
// 	if (!ft_strncmp(, ">", 1))
// 		out_rdirect();
// 	else if (!ft_strncmp(, "<", 1))
// 		in_rdirect();
// 	else if (!ft_strncmp(, ">>", 2))
// 		append_rdirect();
// 	else if (!ft_strncmp(, "<<", 2))
// 		heredoc_rdirect();
// }

void	append_rdirect(t_tree *tree, t_mini *mini)
{
	int	fd_out;
	int	fd_temp;

	fd_out = open(tree->append, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_out < 0)
	{
		if (access(tree->append, F_OK) < 0)
			perror("minishell : <file> No such file or directory");
		else
			perror("open");
	}
	fd_temp = dup(STDOUT_FILENO);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd_out);
	exec_tree(tree, mini);
	if (dup2(fd_temp, STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd_temp);
}

void	out_rdirect(t_tree *tree, t_mini *mini)
{
	int	fd_out;
	int	fd_temp;

	fd_out = open(tree->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		if (access(tree->out, F_OK) < 0)
			perror("minishell : <file> No such file or directory");
		else
			perror("open");
	}
	fd_temp = dup(STDOUT_FILENO);
	if (dup2(fd_out, STDOUT_FILENO) < 0)
		perror("dup2");
	exec_tree(tree, mini);
	if (dup2(fd_temp, STDOUT_FILENO) < 0)
		perror("dup2");
	close(fd_out);
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
	exec_tree(tree, mini);
	if (dup2(fd_temp, STDIN_FILENO) < 0)
		perror("dup2");
	close(fd_in);
	close(fd_temp);
}
