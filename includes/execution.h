/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:17:51 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/19 14:27:16 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

/**
 * @brief Executes the given node in the binary tree.
 *
 * @param node The node to be executed.
 * @param mini A pointer to the minishell struct.
 */
void	exec_node(t_tree *node, t_mini *mini);

/**
 * @brief Checks if the given input is a builtin command.
 *
 * @param input The input command to be checked.
 * @return 1 if the input is a builtin command, 0 otherwise.
 */
int		check_builtin(char *input);

/**
 * @brief Executes an external command.
 *
 * @param cmd The command to be executed.
 * @param mini A pointer to the minishell struct.
 */
void	external_command(char **cmd, t_mini *mini);

/**
 * @brief Executes a builtin command.
 *
 * @param cmd The command to be executed.
 * @param mini A pointer to the minishell struct.
 */
void	exec_builtin(char **cmd, t_mini *mini);

/**
 * @brief Executes a pipe command in the binary tree.
 *
 * @param tree The root of the binary tree.
 * @param mini A pointer to the minishell struct.
 */
void	exec_pipe(t_tree *tree, t_mini *mini);

/**
 * @brief Finds the full path to the given command by searching through
 * the directories specified.
 *
 * @param directories An array of directory paths to search through.
 * @param command The command to find the full path for.
 * @return The full path to the command, or NULL if the command was not found.
 */
char	*get_cmd_path(char **directories, char *command);

/**
 * @brief Finds the full path to the given command by searching through
 * the directories specified.
 *
 * @param command The command to find the full path for.
 * @return The full path to the command, or NULL if the command was not found.
 */
char	*command_path(char *command, t_mini *mini);

void	create_output_files(t_tree *node, t_mini *mini);

#endif
