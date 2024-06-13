/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:17 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/13 15:02:55 by dhasan           ###   ########.fr       */
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

void	finish_rm_env(char **env, char **new_env)
{
	int	i;

	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
	env = new_env;
}

void	rm_env(char **env, int index)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i, sizeof(char *));
	if (!new_env)
		error(E_ALLOC);
	i = 0;
	j = 0;
	while (env[i])
	{
		if (i == index)
		{
			free(env[i]);
			i++;
			continue ;
		}
		new_env[j++] = ft_strdup(env[i++]);
		if (!new_env[j])
			error(E_ALLOC);
	}
	finish_rm_env(env, new_env);
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
				error(E_UNSET);
		rm_env(mini->env, index);
		i++;
	}
}
