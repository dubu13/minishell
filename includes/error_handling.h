/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:12:29 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/15 21:52:18 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H
# define ERROR_HANDLING_H

# include "minishell.h"

/**
 * Prints an error message based on the given error type and input.
 *
 * @param type The type of error.
 * @param input The input that caused the error.
 */
void	error(t_error_type type, char *input);

/**
 * Prints a builtin error message based on the given error type and message.
 *
 * @param type The type of error.
 * @param msg The error message.
 */
void	builtin_msg(t_error_type type, char *msg);

/**
 * Frees the memory allocated for a field and prints an error message.
 *
 * @param field The field to free.
 */
void	free_and_error(char *field);

void	close_and_exit(int *fd, char *msg, t_mini *mini, char *exit_status);

void	free_and_exit(char *msg, t_mini *mini, char *exit_status);

void	msg_for_rdir(char *file, t_mini *mini, int exit_status);

void	msg_for_cmd_node(t_tree *node, t_mini *mini);

#endif