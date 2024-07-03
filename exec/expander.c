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

void	expand_env(t_mini *mini, char *key, int cmd)
{
	char	*value;

	key++;
	value = get_env(mini->env, key);
	if (cmd)
		printf("%s\n", value);
	else
	{
		printf("%s: ", value);
		external_command(value, mini);
	}
}
