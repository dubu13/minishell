/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:23:38 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/19 17:21:40 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Executes a pipe command,
	creating two child processes and connecting them via a pipe.
 * The first child process writes its output to the write end of the pipe,
	and the second
 * child process reads from the read end of the pipe.
 *
 * @param PARAM Placeholder for function parameters,
	which are not provided in the given code.
 * @return 0 on success, or an error code on failure.
 */
// TODO: Implement this function
// TODO: Add error handling
// TODO: Use the functions from the previous exercise to implement this function

int	ft_pipe(PARAM)
{
	int fd[2];
	// fd[0] - read
	// fd[1] - write
	int pid1;
	int pid2;

	if (pipe(fd) == -1) // pipe used to communicate between processes
	{
		ft_printf("PIPE ERROR!\n");
		return (error);
	}
	pid1 = fork(); // fork used to create a new process
	if (pid1 == -1)
	{
		ft_printf("FORK ERROR!\n");
		return (error);
	}
	if (pid1 == 0) // child process 1
	{
		dup2(fd[1], STDOUT_FILENO); // redirect stdout to write end of pipe
		close(fd[0]);               // never read from pipe in child procces
		close(fd[1]);              
			// after writing close the write end of the pipe
		// execute command
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		ft_printf("FORK ERROR!\n");
		return (error);
	}
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO); // redirect stdin to read end of pipe
		close(fd[0]);             
			// after reading close the read end of the pipe
		close(fd[1]);              // never write to pipe in child procces
		// execute command
	}
	close(fd[0]);           // after reading close the read end of the pipe
	close(fd[1]);           // after writing close the write end of the pipe
	waitpid(pid1, NULL, 0); // wait for child process 1 to finish
	waitpid(pid2, NULL, 0); // wait for child process 2 to finish
	return (0);
}