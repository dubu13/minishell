/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:36:30 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/16 14:38:28 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	msg_for_cmd_node(t_tree *node, t_mini *mini)
{
	free_binary(node);
	error(E_ALLOC, NULL);
	mini->exit_status = 1;
}

void	free_and_error(char *field)
{
	free(field);
	error(E_ALLOC, NULL);
}

void	exit_child(t_mini *mini, int status)
{
	free_mini(mini);
	exit(status);
}
