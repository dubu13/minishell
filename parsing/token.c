/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:13:06 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/09 22:59:03 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_ws(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ((input[i] >= 9 && input[i] <= 13) || input[i] == ' '))
		i++;
	return (i);
}

int	is_meta_char(char c)
{
	if (c == '>' || c == '<' || c == '|' || c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_append_heredoc(char *input)
{
	if ((*input == '>' && *(input + 1) == '>')
		|| (*input == '<' && *(input + 1) == '<'))
		return (1);
	return (0);
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return(NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

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

void	handle_append_heredoc(char *input, int *i, t_token **token_list)
{
	int	length;
	char value[3];
	t_token_type	type;
	t_token	*new_token;

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

void	handle_meta_char(char *input, int *i, t_token **token_list)
{
	int	length;
	char	value[2];
	t_token_type	type;
	t_token	*new_token;

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
}

void	handle_word(char *input, int *i, t_token **token_list)
{
	int start;
	char *value;
	int length;
	t_token	*new_token;

	start = *i;
	while (input[*i] && !is_meta_char(input[*i]) && input[*i] != ' ' && input[*i] != '\t' && input[*i] != '\n')
		(*i)++;
	length = *i - start;
	value = malloc(length + 1);
	ft_memcpy(value, &input[start], length);
	value[length] = '\0';
	new_token = create_token(WORD, value);
	add_back_token(token_list, new_token);
	(*i)++;
}

void	token_type(char *input, int *i, t_token **token_list)
{
	while (input[*i])
	{
		if (is_append_heredoc(&input[*i]))
			handle_append_heredoc(input, i, token_list);
			//handle append or heredoc
		else if (is_meta_char(input[*i]))
			handle_meta_char(input, i, token_list);
			//handle meta char
		else if (input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
			handle_word(input, i, token_list);
			//word
	}
}

void	tokenize(char *input, t_token **token_list)
{
	// t_token	*token;
	int		i;

	//skip whitespace
	while (input[i])
	{
		i += skip_ws(&input[i]);
		if (!input[i])
			break;
		token_type(input, &i, token_list);
	}
	

	//check current type
	//-> redirect, pipe, word
	//depending on type, create token
	//add token to linked list
	//until end of input
}
