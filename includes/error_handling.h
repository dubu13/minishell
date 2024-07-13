/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:12:29 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 03:22:09 by dkremer          ###   ########.fr       */
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
void    error(t_error_type type, char *input);

/**
 * Prints a builtin error message based on the given error type and message.
 *
 * @param type The type of error.
 * @param msg The error message.
 */
void    builtin_msg(t_error_type type, char *msg);

#endif