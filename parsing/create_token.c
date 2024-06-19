/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:21:04 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/19 16:21:45 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Creates a new token with the specified type and value.
 *

	* This function allocates memory for a new `t_token` struct and initializes its fields with the provided type and value. The `value` parameter is duplicated using `ft_strdup()` to ensure the token owns its own copy of the value string. The `next` and `prev` pointers are set to `NULL`.
 *
 * @param type   The type of the token to create.
 * @param value  The value of the token to create.
 * @return       A pointer to the newly created token,
	or `NULL` if memory allocation failed.
 */
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

/**
 * Adds a new token to the end of a linked list of tokens.
 *

	* This function takes a pointer to the head of a linked list of tokens and a new token to be added to the list. If the list is empty,
	the new token becomes the head of the list. Otherwise,
	the function traverses the list to the last node and appends the new token to the end of the list,
	updating the `next` and `prev` pointers accordingly.
 *
 * @param head       A pointer to the head of the linked list of tokens.
 * @param new_token  The new token to be added to the list.
 */
void	add_back_token(t_token **head, t_token *new_token)
{
	t_token *current;

	if (!(*head))
		*head = new_token;
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}