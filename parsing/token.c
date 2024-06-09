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

#include "minishell.h"

int	skip_ws(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] >= 9 && input[i] <= 13) || input[i] == ' ')
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

void	handle_word(char *input)
{

}

void	token_type(char *input)
{
	while (*input)
	{
		if (is_append_heredoc(input))
			//handle append or heredoc
		else if (is_meta_char(input))
			//handle meta char
		else
			//word
	}
}

void	tokenize(char *input)
{
	t_token	*token;
	int		i;

	//skip whitespace
	i = skip_ws(input);

	//check current type
	//-> redirect, pipe, word
	//depending on type, create token
	//add token to linked list
	//until end of input
}
