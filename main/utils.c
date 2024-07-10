/* ************************************************************************** */
/*	                                                                       */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 16:49:02 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/27 18:38:39 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_str_closed(char *str)
{
	bool	s_quote_open;
	bool	d_quote_open;

	s_quote_open = false;
	d_quote_open = false;
	while (str && *str != '\0')
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

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\"' && str[i] != '\'')
			new_str[j++] = str[i];
		i++;
	}
	new_str[j] = '\0';
	return (new_str);
}