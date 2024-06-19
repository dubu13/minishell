/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:22:12 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/19 16:22:43 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Skips over any whitespace characters in the input string.
 *
 * This function takes a pointer to a string `input` and returns the number of

	* characters that should be skipped to reach the first non-whitespace character.
 * Whitespace characters are defined as characters with ASCII values between 9
 * and 13 (inclusive), as well as the space character (ASCII value 32).
 *
 * @param input The input string to skip whitespace in.
 * @return The number of whitespace characters to skip.
 */
int	skip_ws(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ((input[i] >= 9 && input[i] <= 13) || input[i] == ' '))
		i++;
	return (i);
}

/**
 * Checks if the given character is a meta character in the shell.
 *
 * Meta characters in the shell include '>', '<', '|', '\'',
	and '"'. This function
 * returns 1 if the input character is a meta character, and 0 otherwise.
 *
 * @param c The character to check.
 * @return 1 if the character is a meta character, 0 otherwise.
 */
int	is_meta_char(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\'' || c == '"')
		return (1);
	return (0);
}

/**
 * Checks if the input string represents an append heredoc operator.
 *
 * This function examines the first two characters of the input string and
 * returns 1 if they represent the append heredoc operator (">>" or "<<"),
 * and 0 otherwise.
 *
 * @param input The input string to check.
 * @return 1 if the input represents an append heredoc operator, 0 otherwise.
 */
int	is_append_heredoc(char *input)
{
	if ((*input == '>' && *(input + 1) == '>') || (*input == '<' && *(input
				+ 1) == '<'))
		return (1);
	return (0);
}