/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 13:33:34 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/21 14:26:44 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Counts the number of pipe tokens in the given token list.
 *
 * @param token_list The linked list of tokens to count pipes in.
 * @return The number of pipe tokens found in the list.
 */
int count_pipes(t_token *token_list)
{
	int pipe_count = 0;
	t_token *current = token_list;

	while (current != NULL)
	{
		if (current->type == PIPE)
			pipe_count++;
		current = current->next;
	}

	return pipe_count;
}