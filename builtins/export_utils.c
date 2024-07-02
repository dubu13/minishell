/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:54:25 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/02 17:16:37 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**

	* Creates a new environment variable array with the given new environment variable added.
 *
 * @param env The existing environment variable array.
 * @param new The new environment variable to be added.

	* @return A newly allocated environment variable array with the new variable added.
 */
char	**new_env(char **env, char *new)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		error(E_ALLOC, NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			error(E_ALLOC, NULL);
		i++;
	}
	new_env[i] = ft_strdup(new);
	if (!new_env[i])
		error(E_ALLOC, NULL);
	free(env);
	return (new_env);
}

/**
 * Sorts the given environment variable array in alphabetical order.
 *
 * @param env The environment variable array to be sorted.
 * @return The sorted environment variable array.
 */
char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

/**
 * Encloses the given environment variable string in double quotes.
 *
 * @param env The environment variable string to be quoted.

	* @return A newly allocated string with the environment variable enclosed in double quotes.
 */
char	*put_quotes(char *env)
{
	char	*key;
	char	*value;
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (ft_strlen(env) == i)
		return (env);
	key = ft_substr(env, 0, i);
	value = ft_strdup(env + i + 1);
	value = ft_strjoin("\"", value);
	value = ft_strjoin(value, "\"");
	key = ft_strjoin(key, "=");
	env = ft_strjoin(key, value);
	free(key);
	free(value);
	return (env);
}
