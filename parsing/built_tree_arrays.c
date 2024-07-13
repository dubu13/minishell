/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree_arrays.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 19:45:49 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/11 14:15:59 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**create_cmd_array(t_token *token, int cmd_count)
{
	char	**cmd_array;
	t_token	*current_token;
	int		i;

	cmd_array = ft_calloc(sizeof(char *), (cmd_count + 1));
	if (!cmd_array)
		return (error(E_ALLOC, NULL), NULL);
	i = 0;
	current_token = token;
	while (current_token && current_token->type != PIPE
		&& (current_token->type == WORD || current_token->type == CMD))
	{
		cmd_array[i++] = ft_strdup(current_token->value);
		current_token = current_token->next;
	}
	return (cmd_array);
}

char	**create_out_array(t_token *token, int out_count)
{
	char	**out_array;
	t_token	*current_token;
	int		i;

	i = 0;
	out_array = ft_calloc(sizeof(char *), (out_count + 1));//
	if (!out_array)
		return (error(E_ALLOC, NULL), NULL);
	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == RDIR_OUT)
			out_array[i++] = ft_strdup(current_token->next->value);//
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
