/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:17 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/10 16:53:34 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**rm_and_copy_env(char **env, char **new_env, int index)
{
	int	i;
	int	j;

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
		new_env[j] = ft_strdup(env[i]);
		free(env[i]);
		if (!new_env[j])
			return (free_array(new_env), error(E_ALLOC, NULL), NULL);
		i++;
		j++;
	}
	free(env);
	return (new_env);
}

char	**rm_env(char **env, int index)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i, sizeof(char *));
	if (!new_env)
		return (error(E_ALLOC, NULL), NULL);
	new_env = rm_and_copy_env(env, new_env, index);
	return (new_env);
}

void	ft_unset(char **input, t_mini *mini)
{
	int	index;
	int	i;

	i = -1;
	index = 0;
	mini->exit_status = 0;
	if (!input)
		return ;
	while (input[++i])
	{
		index = index_env(input[i], mini->env);
		if (index == -1)
			return ;
		if (input[i] && !is_valid_key(input[i]))
		{
			builtin_msg(E_UNSET, input[i]);
			mini->exit_status = 2;
		}
		mini->env = rm_env(mini->env, index);
	}
}
