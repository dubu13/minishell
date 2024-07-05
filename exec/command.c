/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:06:47 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/05 18:53:13 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**

	* Executes the appropriate built-in command based on the tokens in the mini shell.

	* This function iterates through the token list and calls the corresponding built-in
 * function for each recognized command, such as echo, pwd, cd, export, unset,
	and env.

	* The built-in functions are responsible for executing the command and updating the
 * mini shell state as necessary.
 *

	* @param mini The mini shell structure containing the token list and other state.
 */
void	exec_builtin(char **cmd, t_mini *mini)
{
	if (!ft_strncmp(cmd[0], "echo", 4))
		ft_echo(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "pwd", 3))
		ft_pwd(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "env", 3))
		ft_env(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		ft_cd(cmd, mini);
	if (!ft_strncmp(cmd[0], "exit", 4))
		ft_exit(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "export", 6))
		ft_export(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		ft_unset(cmd + 1, mini);
}

int	check_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 4))
		return (1);
	else if (!ft_strncmp(cmd, "pwd", 3))
		return (1);
	else if (!ft_strncmp(cmd, "cd", 2))
		return (1);
	else if (!ft_strncmp(cmd, "export", 6))
		return (1);
	else if (!ft_strncmp(cmd, "unset", 5))
		return (1);
	else if (!ft_strncmp(cmd, "env", 3))
		return (1);
	else if (!ft_strncmp(cmd, "exit", 4))
		return (1);
	return (0);
}

char	*command_path(char *command)
{
	int		i;
	int		len;
	char	*path;
	char	**directories;

	directories = ft_split(getenv("PATH"), ':');
	if (!directories)
		return (ft_putstr_fd \
		("minishell: Path environment variable not found\n", 2), NULL);
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
		if (!(access(path, X_OK | F_OK)))
			return (path);
	}
	return (NULL);
}

char	**check_cmd(char **cmd)
{
	int		i;
	char	*arg;

	i = 0;
	while (cmd[i])
	{
		arg = remove_quotes(cmd[i]);
		free(cmd[i]);
		cmd[i] = arg;
		i++;
	}
	return (cmd);
}

void	external_command(char **cmd, t_mini *mini)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	// char	**cmd;
	// cmd = split_cmd(input, ' ');
	// cmd = check_cmd(cmd);
	if (!cmd)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	cmd_path = command_path(cmd[0]);
	if (!cmd_path)
		error(E_CMD, cmd[0]);
	if (pid == 0)
		execve(cmd_path, cmd, mini->env);
	else
		waitpid(pid, &status, 0);
	free(cmd_path);
	free(cmd);
}