/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:13:06 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 16:19:22 by dkremer          ###   ########.fr       */
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
int skip_ws(char *input)
{
	int i;

	i = 0;
	while (input[i] && ((input[i] >= 9 && input[i] <= 13) || input[i] == ' '))
		i++;
	return (i);
}

/**
 * Checks if the given character is a meta character in the shell.
 *
 * Meta characters in the shell include '>', '<', '|', '\'', and '"'. This function
 * returns 1 if the input character is a meta character, and 0 otherwise.
 *
 * @param c The character to check.
 * @return 1 if the character is a meta character, 0 otherwise.
 */
int is_meta_char(char c)
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
int is_append_heredoc(char *input)
{
	if ((*input == '>' && *(input + 1) == '>') || (*input == '<' && *(input + 1) == '<'))
		return (1);
	return (0);
}

/**
 * Creates a new token with the specified type and value.
 *
 * This function allocates memory for a new `t_token` struct and initializes its fields with the provided type and value. The `value` parameter is duplicated using `ft_strdup()` to ensure the token owns its own copy of the value string. The `next` and `prev` pointers are set to `NULL`.
 *
 * @param type   The type of the token to create.
 * @param value  The value of the token to create.
 * @return       A pointer to the newly created token, or `NULL` if memory allocation failed.
 */
t_token *create_token(t_token_type type, char *value)
{
	t_token *new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

/**
 * Adds a new token to the end of a linked list of tokens.
 *
 * This function takes a pointer to the head of a linked list of tokens and a new token to be added to the list. If the list is empty, the new token becomes the head of the list. Otherwise, the function traverses the list to the last node and appends the new token to the end of the list, updating the `next` and `prev` pointers accordingly.
 *
 * @param head       A pointer to the head of the linked list of tokens.
 * @param new_token  The new token to be added to the list.
 */
void add_back_token(t_token **head, t_token *new_token)
{
	t_token *current;

	if (!(*head))
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}

/**
 * Handles the parsing of a token representing a redirection with append or heredoc.
 *
 * This function is responsible for extracting a token representing a redirection with append ('>>')
 * or heredoc ('<<') from the input string and adding it to the provided token list. It does this
 * by checking the current character in the input string and determining the appropriate token type
 * (RDIR_APPEND or RDIR_HEREDOC). It then creates a new token with the appropriate type and value,
 * and adds it to the token list.
 *
 * The function also advances the index in the input string by the length of the token (2 characters).
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
}

/**
 * Handles the parsing of a meta character token in the input string.
 *
 * This function is responsible for extracting a meta character token from the input string and adding it to the provided token list. It does this by checking the current character in the input string and determining the appropriate token type (RDIR_OUT, RDIR_IN, or PIPE). It then creates a new token with the appropriate type and value, and adds it to the token list.
 *
 * If the next character in the input string is a whitespace character, the function also skips over that whitespace.
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
 * This function is responsible for extracting a word token from the input string and adding it to the provided token list. It does this by iterating through the input string, starting at the current index, and continuing until it encounters a whitespace character or a meta character (such as '>', '<', or '|'). It then extracts the word, creates a new token with the word value, and adds it to the token list.
 *
 * If the next character in the input string is a meta character, the function also calls the `handle_meta_char` function to handle that meta character.
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
}

/**
 * Determines the type of token in the input string and adds it to the provided token list.
 *
 * This function is called by the `tokenize` function to handle the different types of tokens that can
 * appear in the input string. It checks for the following token types:
 *
 * - Append heredoc: Handles the case where the input starts with a "<<" sequence, indicating a heredoc
 *   redirection.
 * - Meta character: Handles the case where the input contains a meta character such as ">", "<", or "|".
 * - Word: Handles the case where the input contains a word (any non-whitespace, non-meta character).
 *
 * For each token type, the appropriate handler function is called to create and add the token to the
 * provided token list.
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
 * This function iterates through the input string, skipping any leading whitespace.
 * For each non-whitespace character, it determines the token type (word, pipe, redirection)
 * and creates a new token, adding it to the provided token list.
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
