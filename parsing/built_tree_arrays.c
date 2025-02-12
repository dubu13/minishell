/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree_arrays.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:45:49 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/19 17:45:13 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_redirections(t_token **current_token)
{
	if ((*current_token)->prev)
	{
		if ((*current_token)->prev->type == RDIR_IN
			|| (*current_token)->prev->type == RDIR_OUT
			|| (*current_token)->prev->type == RDIR_APPEND
			|| (*current_token)->prev->type == RDIR_HEREDOC)
		{
			*current_token = (*current_token)->next;
		}
	}
}

char	**create_cmd_array(t_token *token, int cmd_count, int i)
{
	char	**cmd_array;
	t_token	*current_token;

	cmd_array = ft_calloc(sizeof(char *), (cmd_count + 1));
	if (!cmd_array)
		return (error(E_ALLOC, NULL), NULL);
	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->value[0] == '\0' && !current_token->prev)
		{
			current_token = current_token->next;
			if (!current_token)
				break ;
		}
		if (!current_token || current_token->type == PIPE)
			break ;
		skip_redirections(&current_token);
		if (current_token && (current_token->type == CMD \
			|| current_token->type == WORD))
			cmd_array[i++] = ft_strdup(current_token->value);
		if (current_token && current_token->type != PIPE)
			current_token = current_token->next;
	}
	return (cmd_array);
}

char	**create_in_array(t_token *token, int in_count)
{
	char	**in_array;
	t_token	*current_token;
	int		i;

	i = 0;
	in_array = ft_calloc(sizeof(char *), (in_count + 1));
	if (!in_array)
		return (error(E_ALLOC, NULL), NULL);
	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == RDIR_IN)
			in_array[i++] = ft_strdup(current_token->next->value);
		current_token = current_token->next;
	}
	return (in_array);
}

char	**create_out_array(t_token *token, int out_count)
{
	char	**out_array;
	t_token	*current_token;
	int		i;

	i = 0;
	out_array = ft_calloc(sizeof(char *), (out_count + 1));
	if (!out_array)
		return (error(E_ALLOC, NULL), NULL);
	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == RDIR_OUT)
			out_array[i++] = ft_strdup(current_token->next->value);
		current_token = current_token->next;
	}
	return (out_array);
}

char	**create_append_array(t_token *token, int append_count)
{
	char	**append_array;
	t_token	*current_token;
	int		i;

	i = 0;
	append_array = ft_calloc(sizeof(char *), (append_count + 1));
	if (!append_array)
		return (error(E_ALLOC, NULL), NULL);
	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == RDIR_APPEND)
			append_array[i++] = ft_strdup(current_token->next->value);
		current_token = current_token->next;
	}
	return (append_array);
}
