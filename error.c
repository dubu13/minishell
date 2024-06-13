/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:42:14 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/13 15:02:39 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(t_error_type type)
{
	if (type == E_SYNTAX)
		perror("Syntax error\n");
	if (type == E_CMD)
		perror("Command not found\n");
	if (type == E_PERMISSION)
		perror("Permission denied\n");
	if (type == E_EXPORT)
		perror("Not a valid identifier\n");
	if (type == E_ALLOC)
		perror("Allocation failed\n");
	if (type == E_UNSET)
		perror("Not a valid identifier\n");
}
