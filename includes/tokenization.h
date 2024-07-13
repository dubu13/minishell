/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:16:57 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 03:17:03 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

/**
 * Tokenizes the input string into a linked list of tokens.
 *
 * @param input The input string to be tokenized.
 * @param token_list A pointer to the head of the token list.
 */
void    tokenize(char *input, t_token **token_list);

/**
 * Creates a new token with the specified type and value.
 *
 * @param type The type of the token.
 * @param value The value of the token.
 * @return The newly created token.
 */
t_token *create_token(t_token_type type, char *value);

/**
 * Adds a new token to the end of the token list.
 *
 * @param head A pointer to the head of the token list.
 * @param new_token The new token to be added.
 */
void    add_back_token(t_token **head, t_token *new_token);

/**
 * @brief Checks if the current character in the input string 
 *          is a whitespace character.
 *
 * @param input The input string to check.
 * @return 1 if the current character is a whitespace, 0 otherwise.
 */
int     skip_ws(char *input);

/**
 * @brief Checks if the given character is a meta character.
 *
 * @param c The character to check.
 * @return 1 if the character is a meta character, 0 otherwise.
 */
int     is_meta_char(char c);

/**
 * @brief Checks if the input string contains an append or heredoc redirection.
 *
 * @param input The input string to check.
 * @return 1 if the input contains an append or heredoc redirection, 0 otherwise.
 */
int     is_append_heredoc(char *input);

/**
 * @brief Checks if the character at the given index in the input string 
 *          is not a space.
 *
 * @param input The input string to check.
 * @param i The index of the character to check.
 * @return 1 if the character is not a space, 0 otherwise.
 */
int     is_not_space(char *input, int i);

/**
 * @brief Handles quotes with spaces in the input string.
 *
 * @param input The input string to handle.
 * @param i A pointer to the current index in the input string.
 */
void    handle_quotes_with_space(char *input, int *i);

/**
 * @brief Counts the number of different token types in the token list.
 *
 * @param token The head of the token list.
 * @param counts An array to store the counts of each token type.
 */
void    count_tokens(t_token *token, int *counts);

/**
 * @brief Sets the type of the current token based on the next token.
 *
 * @param is_next_cmd A pointer to a flag indicating if 
 *                      the next token is a command.
 * @return The type of the current token.
 */
t_token_type set_type(int *is_next_cmd);

#endif