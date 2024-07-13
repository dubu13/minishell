/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:41:56 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/13 12:25:11 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	index_env(char *type, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(type);
	while (env[i])
	{
		if (!ft_strncmp(env[i], type, len) && (env[i][len] == '=' \
				|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	update_existing_env(char *temp, char *value, t_mini *mini, int index)
{
	free(mini->env[index]);
	if (value)
		mini->env[index] = ft_strjoin(temp, value);
	else
		mini->env[index] = ft_strdup(temp);
	if (!mini->env[index])
		error(E_ALLOC, NULL);
}

void	update_new_env(char *temp, char *value, t_mini *mini, int env_count)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (env_count + 2));
	if (!new_env)
		error(E_ALLOC, NULL);
	i = 0;
	while (i < env_count)
	{
		new_env[i] = mini->env[i];
		i++;
	}
	if (value)
		new_env[env_count] = ft_strjoin(temp, value);
	else
		new_env[env_count] = ft_strdup(temp);
	if (!new_env[env_count])
		error(E_ALLOC, NULL);
	new_env[env_count + 1] = NULL;
	free(mini->env);
	mini->env = new_env;
}

void	update_env(char *type, char *value, t_mini *mini)
{
	char	*temp;
	int		index;
	int		env_count;

	temp = ft_strjoin(type, "=");
	if (!temp)
		error(E_ALLOC, NULL);
	index = index_env(type, mini->env);
	if (index >= 0)
		update_existing_env(temp, value, mini, index);
	else
	{
		env_count = 0;
		while (mini->env[env_count])
			env_count++;
		update_new_env(temp, value, mini, env_count);
	}
	free(temp);
}

char	*get_env(char **env, char *type)
{
	static char	buffer[4096];
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(type);
	while (env[i])
	{
		if (!ft_strncmp(env[i], type, len) && env[i][len] == '=')
		{
			ft_strlcpy(buffer, env[i] + len + 1, sizeof(buffer));
			return (buffer);
		}
		i++;
	}
	return (NULL);
}

char	**save_env(void)
{
	extern char	**environ;
	char		**env;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (error(E_ALLOC, NULL), NULL);
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		if (!env[i])
			return (error(E_ALLOC, NULL), NULL);
		i++;
	}
	return (env);
}
