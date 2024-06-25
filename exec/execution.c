/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:14:50 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/25 16:09:22 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
to execute external commands need to fork new process :

* The shell process should continue running independently of the command execution.
* The command should execute in its own process context, separate from the shell process.
* After executing the command, the shell needs to wait for its completion and possibly retrieve its exit status.
----------------
ex: Since ls is an external command located in /bin/ls,
you would fork a new process to execute /bin/ls and then wait for its completion.
*/

/*
to execute external commands:
1. fork a new process (fork())
2. execute the command in the child process (execve())
-> need to search for the command in the PATH environment variable
-> /Users/dhasan/.brew/bin:/Users/dhasan/nvim-macos/bin/:/Users/dhasan/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/dhasan/.brew/bin:/Users/dhasan/nvim-macos/bin/:/Users/dhasan/bin
3. wait for the process to complete (waitpid() or wait())
*/
char	*command_path(char *command)
{
	int		i;
	int		len;
	char	*path;
	char	**directories;

	directories = ft_split(getenv("PATH"), ':');
	if (!directories)
		return (ft_putstr_fd("minishell: Path environment variable not found\n", 2), NULL);
	i = -1;
	while (directories[++i])
	{
		len = ft_strlen(directories[i]);
		if (directories[i][len - 1] == '/')
			path = ft_strjoin(directories[i], command);
		else
		{
			path = ft_strjoin(directories[i], "/");
			path = ft_strjoin(path, command);
		}
		// printf("directories: %s\n", path);
		if (!(access(path, X_OK | F_OK)))
			return (path);
	}
	return (NULL);
}

void	external_command(t_token *input, t_mini *mini)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	cmd_path = command_path(input->value);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: command not found: ", 2);
		ft_putstr_fd(input->value, 2);
		ft_putstr_fd("\n", 2);
	}
	if (pid == 0)
		execve(cmd_path, &input->value, mini->env);
	else
		waitpid(pid, &status, 0);
}

void	exec_command(t_mini *mini)
{
	t_token	*current;

	current = mini->token_list;
	while (current)
	{
		if (check_builtin(current))
			exec_builtin(current, mini);
		else
			external_command(current, mini);
		current = current->next;
	}
}
