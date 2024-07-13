/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:16:30 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 03:41:16 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PROCESSING_H
# define INPUT_PROCESSING_H

# include "minishell.h"

/**
 * Checks if a given string is closed (i.e., has matching quotes or parentheses).
 *
 * @param str The string to check.
 * @return 1 if the string is closed, 0 otherwise.
 */
int is_str_closed(char *str);

/**
 * Handles signals received by the minishell program.
 */
void handle_signal(void);

/**
 * Retrieves user input and handles various types of character processing.
 *
 * @param mini The minishell struct.
 * @return The processed user input.
 */
char    *get_input(t_mini *mini);

/**
 * Parses the user input and performs necessary operations.
 *
 * @param mini The minishell struct.
 */
void    parse(t_mini *mini);

/**
 * Handles single quote characters in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @return The processed input string.
 */
char    *handle_single_quote(char **temp, char *new_value);

/**
 * Handles double quote characters in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @param mini The minishell struct.
 * @return The processed input string.
 */
char    *handle_double_quote(char **temp, char *new_value, t_mini *mini);

/**
 * Handles environment variable expansion in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @param mini The minishell struct.
 * @return The processed input string.
 */
char    *handle_env_expansion(char **temp, char *new_value, t_mini *mini);

/**
 * Handles backslash characters in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @return The processed input string.
 */
char    *handle_backslash(char **temp, char *new_value);

/**
 * Handles regular characters in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @return The processed input string.
 */
char    *handle_regular_char(char **temp, char *new_value);
#endif