/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:49:02 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 16:14:48 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if a given string is properly closed with respect to single and double quotes.
 *
 * @param str The string to check.
 * @return 1 if the string is properly closed, 0 otherwise.
 */
int is_str_closed(char *str)
{
	bool s_quote_open;
	bool d_quote_open;

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
