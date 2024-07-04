/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:22:12 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/04 16:04:28 by dkremer          ###   ########.fr       */
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

void	check_next_char(char *input, int *i, t_token **token_list, \
		int *is_next_cmd)
{
	if (input[*i] && is_meta_char(input[*i]))
		handle_meta_char(input, i, token_list, is_next_cmd);
	else
		(*i)++;
	*i += skip_ws(&input[*i]);
}
