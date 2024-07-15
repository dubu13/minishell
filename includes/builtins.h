/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:14:45 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/15 22:11:19 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

/**
 * Prints the arguments to the standard output.
 *
 * @param input The array of arguments to print.
 * @param mini The minishell struct.
 */
void	ft_echo(char **input, t_mini *mini);

/**
 * Changes the current working directory.
 *
 * @param token The array of arguments, with the first element being
 *              the directory to change to.
 * @param mini The minishell struct.
 */
void	ft_cd(char **token, t_mini *mini);

/**
 * Exits the minishell.
 *
 * @param input The array of arguments,
 *              with the first element being the exit status.
 * @param mini The minishell struct.
 */
void	ft_exit(char *input, t_mini *mini);

/**
 * Prints the current working directory.
 *
 * @param cmd The array of arguments (unused).
 * @param mini The minishell struct.
 */
void	ft_pwd(char **cmd, t_mini *mini);

/**
 * Prints the current environment variables.
 *
 * @param input The array of arguments (unused).
 * @param mini The minishell struct.
 */
void	ft_env(char **input, t_mini *mini);

/**
 * Adds or modifies an environment variable.
 *
 * @param input The array of arguments,
 *              with the first element being the variable to export.
 * @param mini The minishell struct.
 */
void	ft_export(char **input, t_mini *mini);

/**
 * Removes an environment variable.
 *
 * @param input The array of arguments,
 *              with the first element being the variable to unset.
 * @param mini The minishell struct.
 */
void	ft_unset(char **input, t_mini *mini);

#endif