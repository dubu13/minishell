/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_processing.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:16:30 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/18 15:29:33 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_PROCESSING_H
# define INPUT_PROCESSING_H

# include "minishell.h"

/**
 * Checks if a given string is closed (i.e.,
	has matching quotes or parentheses).
 *
 * @param str The string to check.
 * @return 1 if the string is closed, 0 otherwise.
 */
int		is_str_closed(char *str);

/**
 * Handles signals received by the minishell program.
 */
void	handle_signal(void);

/**
 * Handles signals received by the minishell program during execution.
 *
 * @param sig The signal received.
 * @param mini The minishell struct.
 */
void	handle_signal_exec(int sig);

/**
 * Retrieves user input and handles various types of character processing.
 *
 * @param mini The minishell struct.
 * @return The processed user input.
 */
char	*get_input(t_mini *mini);

/**
 * Parses the user input and performs necessary operations.
 *
 * @param mini The minishell struct.
 */
void	parse(t_mini *mini);

/**
 * Handles single quote characters in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @return The processed input string.
 */
char	*handle_single_quote(char **temp, char *new_value);

/**
 * Handles double quote characters in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @param mini The minishell struct.
 * @return The processed input string.
 */
char	*handle_double_quote(char **temp, char *new_value, t_mini *mini);

/**
 * Handles environment variable expansion in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @param mini The minishell struct.
 * @return The processed input string.
 */
char	*handle_env_expansion(char **temp, char *new_value, t_mini *mini);

/**
 * Handles backslash characters in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @return The processed input string.
 */
char	*handle_backslash(char **temp, char *new_value);

/**
 * Handles regular characters in the input.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @return The processed input string.
 */
char	*handle_regular_char(char **temp, char *new_value);

/**
 * Expands the input string by handling various types of expansions, \
 * such as environment variable expansion, single quotes, and double quotes.
 *
 * @param temp A pointer to the current input string.
 * @param new_value The new value to be processed.
 * @param mini The minishell struct.
 * @return The expanded input string.
 */
char	*expander(char **temp, char *new_value, t_mini *mini, t_token *token);

/**
 * Converts a string to lowercase.
 *
 * @param str The string to be converted to lowercase.
 * @return The lowercase version of the input string.
 */
char	*ft_str_tolower(char *str);

#endif