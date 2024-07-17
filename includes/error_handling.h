/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:12:29 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/17 16:05:23 by dhasan           ###   ########.fr       */
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

/**
 * Closes the specified file descriptor and exits the program
 *  the given exit status.
 *
 * @param fd The file descriptor to close.
 * @param msg The error message to print before exiting.
 * @param mini The minishell context.
 * @param exit_status The exit status to use when exiting the program.
 */
void	close_and_exit(int *fd, char *msg, t_mini *mini, char *exit_status);

/**
 * Frees the memory allocated for a field and exits the program with \
 * the given exit status.
 *
 * @param msg The error message to print before exiting.
 * @param mini The minishell context.
 * @param exit_status The exit status to use when exiting the program.
 */
void	free_and_exit(char *msg, t_mini *mini, char *exit_status);

/**
 * Prints an error message and exits the program with the given exit
 * status when encountering an issue with a redirected file.
 *
 * @param file The file that caused the error.
 * @param mini The minishell context.
 * @param exit_status The exit status to use when exiting the program.
 */
void	msg_for_rdir(char *file, t_mini *mini, int exit_status);

/**
 * Prints an error message when encountering an issue with a command node.
 *
 * @param node The command node that caused the error.
 * @param mini The minishell context.
 */
void	msg_for_cmd_node(t_tree *node, t_mini *mini);

/**
 * Exits the child process with the specified status.
 *
 * @param mini The minishell context.
 * @param status The exit status to use when exiting the child process.
 */
void	exit_child(t_mini *mini, int status);

#endif