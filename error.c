/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:42:14 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/11 17:31:11 by dhasan           ###   ########.fr       */
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
}
