/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:49:02 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/08 17:05:30 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_closed(char *str)
{
	bool	s_quote_open;
	bool	d_quote_open;

	s_quote_open = false;
	d_quote_open = false;

	while (*str)
	{
		if (*str == '\'')
		{
			if (!d_quote_open)
				s_quote_open = !s_quote_open;
		}
		else if (*str == '"')
		{
			if (!s_quote_open)
				d_quote_open = !d_quote_open;
		}
		str++;
	}
	if (s_quote_open || d_quote_open)
		return (0);
	return (1);
}
