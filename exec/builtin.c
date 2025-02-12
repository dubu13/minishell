/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 19:41:19 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/18 22:42:33 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	{
		if (cmd[1] && cmd[2])
		{
			ft_putendl_fd("exit", 2);
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			mini->exit_status = 1;
		}
		else
			ft_exit(cmd[1], mini);
	}
	else if (!ft_strncmp(cmd[0], "export", 6))
		ft_export(cmd + 1, mini);
	else if (!ft_strncmp(cmd[0], "unset", 5))
		ft_unset(cmd + 1, mini);
}

int	check_builtin(char *cmd)
{
	ft_str_tolower(&cmd[0]);
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
