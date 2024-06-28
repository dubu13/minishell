/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:42:36 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/28 17:22:58 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	c_words(char const *s, char c)
{
	size_t	count;
	int		in_word;
	int		in_quotes;

	count = 0;
	in_word = 0;
	in_quotes = 0;
	while (*s)
	{
		if (*s == '\"')
			in_quotes = !in_quotes;
		else if (*s == c && !in_quotes)
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		s++;
	}
	return (count);
}

static char	**free_m(char **split)
{
	int	i;

	i = -1;
	while (split[++i] != NULL)
		free(split[i]);
	free(split);
	return (NULL);
}

static char	*copy(char const *s, size_t len)
{
	char	*new;
	size_t	i;

	new = ft_calloc(sizeof(char), (len + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = s[i];
	new[len] = '\0';
	return (new);
}

char	**process_string(char const *s, char c, char **split, size_t *i)
{
	size_t	start;
	size_t	end;
	int		in_quotes;

	start = 0;
	end = 0;
	in_quotes = 0;
	while (s[start] != '\0')
	{
		while (s[start] == c && !in_quotes)
			start++;
		end = start;
		while (s[end] != '\0' && (s[end] != c || in_quotes))
			if (s[end++] == '\"')
				in_quotes = !in_quotes;
		if (start != end)
		{
			split[*i] = copy(s + start, end - start);
			if (split[*i] == NULL)
				return (free_m(split));
			(*i)++;
		}
		start = end;
	}
	return (split);
}

char	**split_cmd(char const *s, char c)
{
	char	**split;
	size_t	i;

	i = 0;
	split = ft_calloc(sizeof(char *), (c_words(s, c) + 1));
	if (!split)
		return (NULL);
	split = process_string(s, c, split, &i);
	if (!split)
		return (NULL);
	split[i] = NULL;
	return (split);
}
