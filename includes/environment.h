/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:15:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 03:16:04 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include "minishell.h"

/**
 * Encloses the given environment variable in quotes.
 *
 * @param env The environment variable to enclose in quotes.
 * @return The environment variable enclosed in quotes.
 */
char	*put_quotes(char *env);

/**
 * Sorts the given environment variables in alphabetical order.
 *
 * @param env The array of environment variables to sort.
 * @return The sorted array of environment variables.
 */
char	**sort_env(char **env);

/**
 * Creates a new array of environment variables by adding a new variable.
 *
 * @param env The existing array of environment variables.
 * @param new The new environment variable to add.
 * @return The new array of environment variables with the added variable.
 */
char	**new_env(char **env, char *new);

/**
 * @brief Retrieves the index of an environment variable
 *          in the environment array.
 *
 * @param type The name of the environment variable to search for.
 * @param env The environment array to search.
 * @return The index of the environment variable in the array,
 *          or -1 if not found.
 */
int		index_env(char *type, char **env);

/**
 * @brief Updates the value of an environment variable.
 *
 * @param type The name of the environment variable to update.
 * @param value The new value to set for the environment variable.
 * @param mini The minishell struct.
 */
void	update_env(char *type, char *value, t_mini *mini);

/**
 * @brief Retrieves the value of an environment variable.
 *
 * @param env The environment array to search.
 * @param type The name of the environment variable to retrieve.
 * @return The value of the environment variable, or NULL if not found.
 */
char	*get_env(char **env, char *type);

/**
 * @brief Saves the current environment variables.
 *
 * @return A copy of the current environment array.
 */
char	**save_env(void);

#endif