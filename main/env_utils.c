/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:41:56 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/13 02:27:30 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	index_env(char *type, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(type);
	while (env[i])
	{
		if (!ft_strncmp(env[i], type, len) && \
			(env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

void	update_env(char *type, char *value, t_mini *mini)
{
	char	*temp;
	int		i;

	i = index_env(type, mini->env);
	temp = ft_strjoin(type, "=");
	if (!temp)
		error(E_ALLOC, NULL);
	if (!value)
		mini->env[i] = ft_strdup(temp);
	else
	{
		if (mini->env[i])
			free(mini->env[i]);
		mini->env[i] = ft_strjoin(temp, value);
	}
	if (!mini->env[i])
		error(E_ALLOC, NULL);
	free(temp);
	temp = NULL;
}

char *get_env(char **env, char *type)
{
    static char buffer[4096];
    int i;
	int len;

	i = 0;
    len = ft_strlen(type);
    while (env[i])
    {
        if (!ft_strncmp(env[i], type, len) && env[i][len] == '=')
        {
            ft_strlcpy(buffer, env[i] + len + 1, sizeof(buffer));
            return buffer;
        }
		i++;
    }
    return NULL;
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
