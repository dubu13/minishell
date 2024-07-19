/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:06:47 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/19 14:26:35 by dhasan           ###   ########.fr       */
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

void	execute_child_process(char *cmd_path, char **cmd, t_mini *mini)
{
	if (execve(cmd_path, cmd, mini->env) == -1)
	{
		env_var_msg(cmd[0], mini);
		free(cmd_path);
		exit_child(mini, mini->exit_status);
	}
}

void	wait_for_child(pid_t pid, t_mini *mini)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		mini->exit_status = WEXITSTATUS(status);
}

void	handle_fork_result(pid_t pid, char *cmd_path, char **cmd, t_mini *mini)
{
	if (pid < 0)
	{
		free(cmd_path);
		free_and_exit("minishell: error in fork", mini, "1");
	}
	if (pid == 0)
		execute_child_process(cmd_path, cmd, mini);
	else
		wait_for_child(pid, mini);
	free(cmd_path);
}

void	external_command(char **cmd, t_mini *mini)
{
	char	*cmd_path;
	pid_t	pid;

	if (!cmd)
		return ;
	cmd_path = command_path(cmd[0], mini);
	if (!cmd_path)
	{
		env_var_msg(cmd[0], mini);
		return ;
	}
	pid = fork();
	handle_fork_result(pid, cmd_path, cmd, mini);
}
