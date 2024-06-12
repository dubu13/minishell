/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:17 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/12 22:44:13 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//lets say args[0] = unset
//args[1] = NAME

int	is_valid_key(char *key)
{
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

void	rm_env(char **env, int index)
{
	char	**new_env;
}

void	ft_unset(char **args, t_mini *mini)
{
	int	index;
	int	i;

	i = 1;
	if (args[i] == NULL )
		return ;
	while (args[i])
	{
		index = index_env(args[i], mini->env);
		if (index == -1)
			return ;
		if (args[i])
			if (!is_valid_key(args[i]))
				error();
		rm_env(mini->env, index);
		i++;
	}
}
