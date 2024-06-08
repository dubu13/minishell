/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:41:56 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/08 17:37:08 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	index_env(char *type, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(type);
	while (env[i])
	{
		if (!ft_strncmp(env[i], type, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env(char *type, char *path, t_mini *mini)
{
	char	*temp;
	int		i;

	i = index_env(type, mini->env);
	if (i == -1)
		exit (EXIT_FAILURE);
	free(mini->env[i]);
	temp = ft_strjoin(type, "=");
	mini->env[i] = ft_strjoin(temp, path);
	free(temp);
}

char	*get_env(char **env, char *type)
{
	int	i;
	int	len;

	i = index_env(type, env);
	if (i == -1)
		return (ft_strdup(""));
	len = ft_strlen(type);
	return (ft_strdup(env[i] + len + 1));
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
		return (perror("Calloc"), NULL);
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		if (!env[i])
			return (perror("Strdup"), NULL);
		i++;
	}
	return (env);
}
