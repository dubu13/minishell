/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 13:41:56 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 16:15:47 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Finds the index of an environment variable in an environment array.
 *
 * This function takes an environment variable name and an environment array,
 * and returns the index of the first matching environment variable in the
 * array. If the variable is not found, it returns -1.
 *
 * @param type The name of the environment variable to search for.
 * @param env The environment array to search.
 * @return The index of the matching environment variable, or -1 if not found.
 */
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

/**
 * Updates an environment variable in the shell's environment.
 *
 * This function takes an environment variable name, a new value for that
 * variable, and a pointer to the shell's environment. It finds the index of
 * the environment variable in the environment array, frees the old value, and
 * sets the new value.
 *
 * @param type The name of the environment variable to update.
 * @param path The new value to set for the environment variable.
 * @param mini A pointer to the shell's environment.
 */
void	update_env(char *type, char *path, t_mini *mini)
{
	char	*temp;
	int		i;

	i = index_env(type, mini->env);
	// if (i == -1)
	// 	exit (EXIT_FAILURE);
	free(mini->env[i]);
	temp = ft_strjoin(type, "=");
	mini->env[i] = ft_strjoin(temp, path);
	free(temp);
}

/**
 * Retrieves the value of an environment variable.
 *
 * This function takes an array of environment variables and a variable name,
 * and returns the value of the corresponding environment variable. If the
 * variable is not found in the environment, an empty string is returned.
 *
 * @param env The array of environment variables.
 * @param type The name of the environment variable to retrieve.
 * @return The value of the environment variable, or an empty string if the
 * variable is not found.
 */
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

/**
 * Saves a copy of the current environment variables.
 *
 * This function creates a dynamically allocated copy of the current environment
 * variables, which can be used to restore the environment later. The copy is
 * allocated using `ft_calloc` and each environment variable is duplicated using
 * `ft_strdup`.
 *
 * @return A null-terminated array of strings representing the environment
 * variables, or `NULL` if the allocation fails.
 */
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
