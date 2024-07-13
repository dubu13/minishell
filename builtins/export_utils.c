/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 21:54:25 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/13 12:22:21 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**new_env(char **env, char *new)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return (error(E_ALLOC, NULL), NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_array(new_env), error(E_ALLOC, NULL), NULL);
		free(env[i]);
		i++;
	}
	free(env);
	new_env[i] = ft_strdup(new);
	if (!new_env[i])
		return (free_array(new_env), error(E_ALLOC, NULL), NULL);
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
	char	*tmp;
	size_t	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (ft_strlen(env) == i)
		return (env);
	key = ft_substr(env, 0, i);
	tmp = ft_strdup(env + i + 1);
	value = ft_strjoin("\"", tmp);
	free(tmp);
	tmp = ft_strjoin(value, "\"");
	free(value);
	value = ft_strjoin(key, "=");
	env = ft_strjoin(value, tmp);
	free(tmp);
	free(key);
	free(value);
	return (env);
}
