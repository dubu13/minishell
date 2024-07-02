/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:42:14 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/02 18:12:49 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints an error message to stderr based on the specified error type.
 *
 * @param type The type of error that occurred.
 * @param input The input that caused the error, if applicable.
 */
void	error(t_error_type type, char *input)
{
	if (type == E_SYNTAX)
	{
		ft_putstr_fd("syntax error\n", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\n", 2);
	}
	if (type == E_CMD)
	{
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": command not found\n");
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
		ft_putstr_fd(input, 2);
	}
	if (type == E_UNSET)
	{
		ft_putstr_fd("unset: not a valid identifier : ", 2);
		ft_putstr_fd(input, 2);
	}
	if (type == E_EXIT)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd(": numeric argument required", 2);
	}
	if (type == E_CD)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(input, 2);
	}
	ft_putstr_fd("\n", 2);
}
