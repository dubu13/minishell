/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:54:25 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/07 05:33:03 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
