/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:44:42 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/24 21:21:59 by dhasan           ###   ########.fr       */
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

void	out_rdirect()
{
	int	fd_out;
	int	fd_temp;

	fd_out = open("file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		if (access("file", F_OK) < 0)
			perror("minishell : <file> No such file or directory");
		else
			perror("open");
	}
	fd_temp = dup(STDOUT_FILENO);//save stdout so we can restore it after exec
	if (dup2(fd_out, STDOUT_FILENO) < 0)//redirect stdout to file so, exec will write to file
		perror("dup2");
	// exec_builtin();
	if (dup2(fd_temp, STDOUT_FILENO) < 0)//restore stdout
		perror("dup2");
	close(fd_out);
	close(fd_temp);
}

void	in_rdirect()
{
	int	fd_in;
	int	fd_temp;

	fd_in = open("file", O_WRONLY);
	if (fd_in < 0)
	{
		if (access("file", F_OK) < 0)
			perror("minishell : <file> No such file or directory");
		else
			perror("open");
	}
	fd_temp = dup(STDIN_FILENO);//save stdin so we can restore it after exec
	if (dup2(fd_in, STDIN_FILENO) < 0)//redirect stdin to file so, exec will write to file
		perror("dup2");
	// exec_builtin();
	if (dup2(fd_temp, STDIN_FILENO) < 0)//restore stdin
		perror("dup2");
	close(fd_in);
	close(fd_temp);
}
