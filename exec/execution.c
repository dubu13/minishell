/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:14:50 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/03 16:31:30 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_command(t_mini *mini)
{
	int		i;

	i = 0;
	while (mini->cmd_list[i])
	{
		if (check_builtin(mini->cmd_list[i]))
			exec_builtin(mini);
		else if (!ft_strncmp(mini->cmd_list[i], "$", 1))
			expand_env(mini, mini->cmd_list[i], 0);
		else
			external_command(mini->cmd_list[i], mini);
		i++;
	}
}
