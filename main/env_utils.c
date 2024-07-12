/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:41:56 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/10 17:09:37 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	len_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

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
	// free(mini->env[i]);
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

char	*get_env(char **env, char *type)
{
	int	i;
	int	len;

	i = index_env(type, env);
	if (i == -1)
		return (NULL);
		// return (ft_strdup(""));
	len = ft_strlen(type);
	return (ft_strdup(env[i] + len + 1));
}

char	**save_env(void)
{
	extern char	**environ;
	char		**env;
	int			i;
	int			oldpwd;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "OLDPWD", 6))
			oldpwd = 0;
		i++;
	}
	if (!oldpwd)
		env = ft_calloc(i + 2, sizeof(char *));
	else
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
	if (!oldpwd)
		env[i] = ft_strdup("OLDPWD");
	return (env);
}
