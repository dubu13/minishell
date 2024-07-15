/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:06:47 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/15 20:21:54 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env_var_msg(char *cmd, t_mini *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (cmd[0] == '/')
	{
		if (!access(cmd, F_OK))
		{
			ft_putendl_fd(": Is a directory", 2);
			mini->exit_status = 126;
		}
		else
		{
			ft_putendl_fd(": No such file or directory", 2);
			mini->exit_status = 127;
		}
	}
	else
	{
		ft_putendl_fd(": command not found", 2);
		mini->exit_status = 127;
	}
}

char	*get_cmd_path(char **directories, char *command)
{
	int		i;
	int		len;
	char	*path;
	char	*temp;

	i = -1;
	while (directories[++i])
	{
		len = ft_strlen(directories[i]);
		if (directories[i][len - 1] == '/')
			path = ft_strjoin(directories[i], command);
		else
		{
			temp = ft_strjoin(directories[i], "/");
			path = ft_strjoin(temp, command);
			free(temp);
		}
		if (!(access(path, X_OK | F_OK)))
			return (path);
		free(path);
	}
	return (NULL);
}

char	*command_path(char *command)
{
	char	**directories;
	char	*path;

	if (!ft_strncmp(command, "/", 1) || !ft_strncmp(command, "./", 2) \
		|| !ft_strncmp(command, "../", 3))
	{
		if (!access(command, X_OK | F_OK))
			return (ft_strdup(command));
		else
			return (NULL);
	}
	directories = ft_split(getenv("PATH"), ':');
	if (!directories)
		return (ft_putendl_fd \
		("minishell: Path environment variable not found", 2), NULL);
	path = get_cmd_path(directories, command);
	free_array(directories);
	return (path);
}

void	external_command(char **cmd, t_mini *mini)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	if (!cmd)
		return ;
	cmd_path = command_path(cmd[0]);
	pid = fork();
	if (pid < 0)
	{
		free(cmd_path);
		free_and_exit("minishell: error in fork", mini, "1");
	}
	if (pid == 0)
	{
		if (execve(cmd_path, cmd, mini->env) == -1)
		{
			env_var_msg(cmd[0], mini);
			free(cmd_path);
			free_and_exit("minishell: command execution failed", mini, "127");
		}
	}
	else
		waitpid(pid, &status, 0);
	free(cmd_path);
}
