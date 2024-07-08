/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:06:47 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/07 13:50:02 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(char **cmd, t_mini *mini)
{
	if (!ft_strncmp(cmd[0], "echo", 4))
		ft_echo(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "pwd", 3))
		ft_pwd(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "env", 3))
		ft_env(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "cd", 2))
		ft_cd(cmd + 1, mini);
	if (!ft_strncmp(cmd[0], "exit", 4))
		ft_exit(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "export", 6))
		ft_export(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		ft_unset(cmd + 1, mini);
}

int	check_builtin(char *cmd)
{
	if (!ft_strncmp(cmd, "echo", 5) || \
		!ft_strncmp(cmd, "pwd", 4) || \
		!ft_strncmp(cmd, "cd", 3) || \
		!ft_strncmp(cmd, "export", 7) || \
		!ft_strncmp(cmd, "unset", 6) || \
		!ft_strncmp(cmd, "env", 4) || \
		!ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}

void	env_var_msg(char *cmd, t_mini *mini)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	if (cmd[0] == '/')
	{
		if (!access(cmd, F_OK))
		{
			ft_putstr_fd(": Is a directory\n", 2);
			mini->exit_status = 126;
		}
		else
		{
			ft_putstr_fd(": No such file or directory\n", 2);
			mini->exit_status = 127;
		}
	}
	else
	{
		ft_putstr_fd(": command not found\n", 2);
		mini->exit_status = 127;
	}
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
	free_array(directories);
	// free(path);
	return (NULL);
}

void	external_command(char **cmd, t_mini *mini)
{
	char	*cmd_path;
	pid_t	pid;
	int		status;

	if (!cmd)
		return ;
	cmd_path = command_path(cmd[0]);
	if (!cmd_path)
		env_var_msg(cmd[0], mini);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		execve(cmd_path, cmd, mini->env);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	free(cmd_path);
}
