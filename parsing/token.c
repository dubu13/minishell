/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 20:13:06 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/08 13:33:08 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_append_heredoc(char *input, int *i, t_token **token_list)
{
	int				length;
	char			value[3];
	t_token_type	type;
	t_token			*new_token;

	length = 2;
	if (input[*i] == '>')
		type = RDIR_APPEND;
	else
		type = RDIR_HEREDOC;
	ft_strlcpy(value, &input[*i], length + 1);
	new_token = create_token(type, value);
	if (!new_token)
		error(E_ALLOC, NULL);
	add_back_token(token_list, new_token);
	(*i) += length;
	*i += skip_ws(&input[*i]);
}

void	handle_meta_char(char *input, int *i, t_token **token_list,
		int *is_next_cmd)
{
	int				length;
	char			value[2];
	t_token_type	type;
	t_token			*new_token;

	length = 1;
	if (input[*i] == '>')
		type = RDIR_OUT;
	else if (input[*i] == '<')
		type = RDIR_IN;
	else
		type = PIPE;
	ft_strlcpy(value, &input[*i], length + 1);
	new_token = create_token(type, value);
	if (!new_token)
		error(E_ALLOC, NULL);
	add_back_token(token_list, new_token);
	(*i) += length;
	*i += skip_ws(&input[*i]);
	if (type == PIPE)
		*is_next_cmd = 1;
	else
		*is_next_cmd = 0;
}

void	handle_word(char *input, int *i, t_token **token_list, int *is_next_cmd)
{
	int				start;
	int				length;
	char			*value;
	t_token_type	type;
	t_token			*new_token;

	start = *i;
	while (is_not_space(input, *i))
		(*i)++;
	length = *i - start;
	value = ft_calloc(length + 1, sizeof(char));
	if (!value)
		error(E_ALLOC, NULL);
	ft_strlcpy(value, &input[start], length + 1);
	value[length] = '\0';
	type = set_type(is_next_cmd);
	new_token = create_token(type, value);
	if (!new_token)
		free_and_error(value, E_ALLOC, NULL);
	add_back_token(token_list, new_token);
	*is_next_cmd = 0;
	if (input[*i] && is_meta_char(input[*i]))
		handle_meta_char(input, i, token_list, is_next_cmd);
	*i += skip_ws(&input[*i]);
	// free(value);
}

void	token_type(char *input, int *i, t_token **token_list, int *is_next_cmd)
{
	while (input[*i])
	{
		if (is_append_heredoc(&input[*i]))
			handle_append_heredoc(input, i, token_list);
		else if (is_meta_char(input[*i]))
			handle_meta_char(input, i, token_list, is_next_cmd);
		else if (input[*i] != '|' && input[*i] != '<' && input[*i] != '>')
			handle_word(input, i, token_list, is_next_cmd);
	}
}

void	tokenize(char *input, t_token **token_list)
{
	int	i;
	int	is_next_cmd;

	i = 0;
	is_next_cmd = 1;
	if (input)
	{
		while (input[i] != '\0')
		{
			i += skip_ws(&input[i]);
			if (input[i] == '\0')
				break ;
			token_type(input, &i, token_list, &is_next_cmd);
		}
	}
}
