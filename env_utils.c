/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:41:56 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/29 15:54:36 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// checks in env type env if its finds it returns the path
// else return empty string
//ex: type is "HOME"
//env -> [i] = "HOME=/Users/dhasan" -> returns /Users/dhasan
char	get_env(char **env, char *type)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(type);
	while (env[i])
	{
		if (!ft_strncmp(env, type, len) && env[i][len] == '=')
			return (ft_strdup(env[i] + len + 1));
		i++;
	}
	return (ft_strdup(""));
}

//this func gonna check type in env and gonna return the pos (index) of type
//ex: type is "HOME"
//env -> [i] = "HOME=/Users/dhasan" -> returns the i
int	index_env(char *type, char **env)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(type);
	while (env[i])
	{
		if (!ft_strncmp(env, type, len) && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
