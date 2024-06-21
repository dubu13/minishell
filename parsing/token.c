/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:13:06 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/21 17:50:41 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Handles the parsing of a token that represents a redirection to append or a here-document.
 *
 * This function is responsible for extracting a token from the input string that represents either a redirection to append ('>>')
 * or a here-document ('<<'). It creates a new token with the appropriate type and value, and adds it to the provided token list.
 *
 * If the next character in the input string is a whitespace character, the function also skips over that whitespace.
 *
 * @param input       The input string being tokenized.
 * @param i           A pointer to the current index in the input string.
 * @param token_list  A pointer to the token list to which the tokens will be added.
 */
void handle_append_heredoc(char *input, int *i, t_token **token_list)
{
	int length;
	char value[3];
	t_token_type type;
	t_token *new_token;

	length = 2;
	if (input[*i] == '>')
		type = RDIR_APPEND;
	else
		type = RDIR_HEREDOC;
	ft_strlcpy(value, &input[*i], length + 1);
	new_token = create_token(type, value);
	add_back_token(token_list, new_token);
	(*i) += length;
	*i += skip_ws(&input[*i]);
}

/**
 * Handles the parsing of a meta character (such as '>', '<', or '|') in the input string.
 *
 * This function is responsible for identifying the type of meta character encountered (redirection or pipe) and creating a new token for it. It then adds the new token to the provided token list.
 *
 * @param input       The input string being tokenized.
 * @param i           A pointer to the current index in the input string.
 * @param token_list  A pointer to the token list to which the tokens will be added.
 */
void handle_meta_char(char *input, int *i, t_token **token_list)
{
	int length;
	char value[2];
	t_token_type type;
	t_token *new_token;

	length = 1;
	if (input[*i] == '>')
		type = RDIR_OUT;
	else if (input[*i] == '<')
		type = RDIR_IN;
	else
		type = PIPE;
	ft_strlcpy(value, &input[*i], length + 1);
	new_token = create_token(type, value);
	add_back_token(token_list, new_token);
	(*i) += length;
	*i += skip_ws(&input[*i]);
}

/**
 * Handles the parsing of a word token in the input string.
 *
 * This function is responsible for identifying a word token, extracting its value, creating a new token, and adding it to the provided token list.
 * If a meta character (such as '>', '<', or '|') is encountered after the word, the function will also call the `handle_meta_char` function to process the meta character.
 *
 * @param input       The input string being tokenized.
 * @param i           A pointer to the current index in the input string.
 * @param token_list  A pointer to the token list to which the tokens will be added.
 */
void handle_word(char *input, int *i, t_token **token_list)
{
	int start;
	char *value;
	int length;
	t_token *new_token;

	start = *i;
	while (input[*i] && !is_meta_char(input[*i]) && input[*i] != ' ' && input[*i] != '\t' && input[*i] != '\n')
		(*i)++;
	length = *i - start;
	value = malloc(length + 1);
	ft_memcpy(value, &input[start], length);
	value[length] = '\0';
	new_token = create_token(WORD, value);
	add_back_token(token_list, new_token);
	if (input[*i] && is_meta_char(input[*i]))
		handle_meta_char(input, i, token_list);
	else
		(*i)++;
	*i += skip_ws(&input[*i]);
}

/**
 * Handles the different token types that can be encountered in the input string.
 * This function is responsible for identifying the token type (word, pipe, redirection)
 * and calling the appropriate handler function to process the token.
 *
 * @param input       The input string being tokenized.
 * @param i           A pointer to the current index in the input string.
 * @param token_list  A pointer to the token list to which the tokens will be added.
 */
void token_type(char *input, int *i, t_token **token_list)
{
	while (input[*i])
	{
		if (is_append_heredoc(&input[*i]))
			handle_append_heredoc(input, i, token_list);
		else if (is_meta_char(input[*i]))
			handle_meta_char(input, i, token_list);
		else if (input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
			handle_word(input, i, token_list);
	}
}

/**
 * Tokenizes the input string and adds the resulting tokens to the provided token list.
 *
 * This function is responsible for iterating through the input string and identifying the different token types (word, pipe, redirection, etc.).
 * It calls the appropriate handler functions to process each token and add it to the token list.
 *
 * @param input       The input string to be tokenized.
 * @param token_list  A pointer to the token list to which the tokens will be added.
 */
void tokenize(char *input, t_token **token_list)
{
	int i;

	i = 0;
	while (input[i])
	{
		i += skip_ws(&input[i]);
		if (!input[i])
			break;
		token_type(input, &i, token_list);
	}
}
