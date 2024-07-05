/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:22:12 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/05 19:02:40 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_ws(char *input)
{
	int	i;

	i = 0;
	while (input[i]\
		&& ((input[i] == '\t' || input[i] == '\n') || input[i] == ' '))
		i++;
	return (i);
}

int	is_meta_char(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	is_append_heredoc(char *input)
{
	if ((*input == '>' && *(input + 1) == '>') || (*input == '<' && *(input
				+ 1) == '<'))
		return (1);
	return (0);
}

t_token_type	set_type(int *is_next_cmd)
{
	if (*is_next_cmd)
	{
		*is_next_cmd = 0;
		return (CMD);
	}
	else
		return (WORD);
}
