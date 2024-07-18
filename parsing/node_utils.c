/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 16:21:04 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/18 21:51:08 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*initialize_node(t_token *token)
{
	t_tree	*node;

	node = ft_calloc(sizeof(t_tree), 1);
	if (!node)
		return (NULL);
	node->type = token->type;
	return (node);
}

void	add_front(t_token **lst, t_token *new)
{
	new->next = *lst;
	*lst = new;
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		error(E_ALLOC, NULL);
		return (NULL);
	}
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	add_back_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (*head == NULL)
		*head = new_token;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
		new_token->prev = current;
	}
}
