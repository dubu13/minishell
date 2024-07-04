/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:13:09 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/03 16:34:48 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//just $KEY: $HOME (HOME=/root) -> minishell: /root: is a directory
// with echo: echo $HOME (HOME=/root) -> /root
//$? - exit status of the last command

void	handle_env_var(t_mini *mini)
{
	t_token	*current;
	char	*value;

	current = mini->token_list;
	value = NULL;
	while (current)
	{
		if (current->type == WORD)
		{
			if (current->value[0] == '$')
			{
				if (current->value[1] == '?')
				{
					//free(current->value);
					//current->value = ft_itoa(mini->exit_status);
				}
				else if (current->value[1] != '\0')
				{
					value = get_env(mini->env, current->value + 1);
					current->value = value;
				}
			}
		}
		current = current->next;
	}
}
