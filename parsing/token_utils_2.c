/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 19:07:13 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/15 21:37:53 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_not_space(char *input, int i)
{
	if ((input[i] && !is_meta_char(input[i]) && input[i] != ' ' \
		&& input[i] != '\t' && input[i] != '\n'))
		return (1);
	else
		return (0);
}

void	handle_quotes_with_space(char *input, int *i)
{
	int	quote;

	quote = 0;
	while (input[*i] && (is_not_space(input, *i) || quote))
	{
		if ((input[*i] == '"' || input[*i] == '\'') && !quote)
		{
			quote = input[*i];
		}
		else if (input[*i] == quote)
		{
			quote = 0;
		}
		(*i)++;
	}
}
