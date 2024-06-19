/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:37:00 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 17:17:18 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_builtin(t_mini *mini)
{
	t_token	*current;

	current = mini->token_list;
	while (current)
	{
		if (!ft_strncmp(current->value, "echo", 4))
			ft_echo(current->next);
		if (!ft_strncmp(current->value, "pwd", 3))
			ft_pwd();
		if (!ft_strncmp(current->value, "cd", 2))
			ft_cd(current->next, mini);
		// if (!ft_strncmp(current->value, "exit", 4))
		// 	return ();
		if (!ft_strncmp(current->value, "export", 6))
			return (ft_export(current->next, mini));
		if (!ft_strncmp(current->value, "unset", 5))
			return (ft_unset(current->next, mini));
		if (!ft_strncmp(current->value, "env", 3))
			return (ft_env(current->next, mini));
		current = current->next;
	}
}
