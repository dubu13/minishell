/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:23:38 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/28 17:43:05 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Allocates memory for an array of pipe file descriptors and an array of process IDs.
 *
 * This function is responsible for dynamically allocating memory for the pipes and process IDs
 * that will be used in the pipeline of commands. It allocates memory for an array of pipe file
 * descriptors and an array of process IDs, with the size of the arrays determined by the
 * `pipe_count` parameter.
 *
 * @param pipes A double pointer to an array of pipe file descriptors. This array will be
 *              allocated by this function.
 * @param pids A double pointer to an array of process IDs. This array will be allocated by
 *             this function.
 * @param pipe_count The number of pipes to allocate in the `pipes` array.
 */
static void	allocate_resources(int ***pipes, pid_t **pids, int pipe_count)
{
	*pipes = malloc(sizeof(int *) * (pipe_count + 1));
	if (*pipes == NULL)
		error(E_ALLOC, NULL);
	*pids = malloc(sizeof(pid_t) * (pipe_count + 2));
	if (*pids == NULL)
		error(E_ALLOC, NULL);
}

/**
 * Allocates and initializes an array of pipe file descriptors.
 *
 * @param pipes A double pointer to an array of pipe file descriptors.
 * @param pipe_count The number of pipes to allocate.
 */
static void	setup_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (pipes[i] == NULL)
			error(E_ALLOC, NULL);
		i++;
	}
}

/**
 * Closes all the pipe file descriptors in the given array of pipes.
 *
 * @param pipes A double pointer to an array of pipe file descriptors.
 * @param pipe_count The number of pipes to close.
 */
static void	close_pipes(int **pipes, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

/**
 * Executes a child process in a pipeline, handling input and output redirection.
 *
 * This function is called by the parent process in the ft_pipe function to execute
 * a child process in the pipeline. It sets up the necessary input and output
 * redirection for the child process based on its position in the pipeline.
 *
 * @param mini A pointer to the t_mini struct containing the mini shell state.
 * @param token_list A pointer to the linked list of tokens representing the pipeline.
 * @param pipes A 2D array of pipe file descriptors, one for each pipe in the pipeline.
 * @param child_index The index of the current child process in the pipeline.
 */
static void	exec_child(t_mini *mini, t_token *token_list, int **pipes, \
				int child_index)
{
	int	pipe_count;

	pipe_count = count_pipes(token_list);
	if (child_index == 0)
	{
		dup2(pipes[0][1], STDOUT_FILENO);
		close(pipes[0][0]);
	}
	else if (child_index == pipe_count)
	{
		dup2(pipes[child_index - 1][0], STDIN_FILENO);
		close(pipes[child_index - 1][1]);
	}
	else
	{
		dup2(pipes[child_index - 1][0], STDIN_FILENO);
		close(pipes[child_index - 1][1]);
		dup2(pipes[child_index][1], STDOUT_FILENO);
		close(pipes[child_index][0]);
	}
	close_pipes(pipes, pipe_count);
	exec_builtin(mini);
	exit(EXIT_FAILURE);
}

/**
 * Executes a pipeline of child processes, handling input and output redirection.
 *
 * This function is responsible for setting up and executing a pipeline of child
 * processes, where the output of one process is used as the input for the next.
 * It allocates the necessary resources, sets up the pipes, forks the child
 * processes, and waits for them to complete.
 *
 * @param mini A pointer to the t_mini struct containing the mini shell state.
 * @param token_list A pointer to the linked list of tokens representing the pipeline.
 * @return 0 on success, or a non-zero exit status on failure.
 */
int	ft_pipe(t_mini *mini, t_token *token_list)
{
	int		pipe_count;
	int		**pipes;
	int		i;
	pid_t	*pids;

	pipe_count = count_pipes(token_list);
	allocate_resources(&pipes, &pids, pipe_count);
	setup_pipes(pipes, pipe_count);
	i = 0;
	while (i <= pipe_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			exit(EXIT_FAILURE);
		else if (pids[i] == 0)
			exec_child(mini, token_list, pipes, i);
		i++;
	}
	i = 0;
	while (i <= pipe_count)
		waitpid(pids[i++], NULL, 0);
	close_pipes(pipes, pipe_count);
	free(pipes);
	free(pids);
	return (0);
}
void execute_pipeline(char **commands, int num_commands)
{
    int i;
    int pipe_fds[2];
    int prev_fd = 0;  // Initially, no previous fd

    for (i = 0; i < num_commands; i++)
    {
        pipe(pipe_fds);  // Create a pipe for the next command

        if (fork() == 0)
        {
            // Child process

            if (i > 0)
            {
                // Not the first command, get input from previous pipe
                dup2(prev_fd, 0);
                close(prev_fd);
            }

            if (i < num_commands - 1)
            {
                // Not the last command, output to next pipe
                dup2(pipe_fds[1], 1);
            }

            // Close the pipe ends that are not needed
            close(pipe_fds[0]);
            close(pipe_fds[1]);

            // Execute the command
            exec_command(commands[i]);
            exit(EXIT_FAILURE);  // exec_command only returns on failure
        }
        else
        {
            // Parent process

            // Close the write end of the pipe in the parent
            close(pipe_fds[1]);

            // Save the read end of the pipe to be used as input for the next command
            prev_fd = pipe_fds[0];
        }
    }

    // Wait for all child processes to finish
    for (i = 0; i < num_commands; i++)
    {
        wait(NULL);
    }
}
