/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:42:14 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/18 17:20:54 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_error_type type, char *input)
{
	if (type == E_SYNTAX)
		perror("Syntax error\n");
	if (type == E_CMD)
		perror("Command not found\n");
	if (type == E_PERMISSION)
		perror("Permission denied\n");
	if (type == E_ALLOC)
		perror("Allocation failed\n");
	if (type == E_EXPORT)
	{
		ft_putstr_fd("export: not a valid identifier : ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\n", 2);
	}
	if (type == E_UNSET)
	{
		ft_putstr_fd("unset: not a valid identifier : ", 2);
		ft_putstr_fd(input, 2);
		ft_putstr_fd("\n", 2);
	}
}
