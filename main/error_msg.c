/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:42:14 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/15 18:27:51 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error(t_error_type type, char *input)
{
	if (type == E_SYNTAX)
	{
		ft_putstr_fd("syntax error: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\n", 2);
	}
	if (type == E_PERMISSION)
		perror("Permission denied\n");
	if (type == E_ALLOC)
		perror("Allocation failed\n");
}

void	builtin_msg(t_error_type type, char *msg)
{
	if (type == E_EXPORT)
	{
		ft_putstr_fd("export: not a valid identifier : ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (type == E_UNSET)
	{
		ft_putstr_fd("unset: not a valid identifier : ", 2);
		ft_putstr_fd(msg, 2);
	}
	if (type == E_EXIT)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": numeric argument required", 2);
	}
	if (type == E_CD)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(msg, 2);
	}
	ft_putstr_fd("\n", 2);
}

void	close_and_exit(int *fd, char *msg, t_mini *mini, char *exit_status)
{
	close(fd[0]);
	close(fd[1]);
	free_and_exit(msg, mini, exit_status);
}

void	free_and_exit(char *msg, t_mini *mini, char *exit_status)
{
	perror(msg);
	ft_exit(&exit_status, mini);
}
