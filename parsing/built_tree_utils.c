/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:55:23 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/10 19:14:52 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*initialize_node(t_token *token)
{
	t_tree	*node;

	node = ft_calloc(sizeof(t_tree), 1);
	if (!node)
		return (NULL);
	node->type = token->type;
	return (node);
}

void	count_tokens(t_token *token, int *counts)
{
	t_token	*current_token;

	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == CMD || current_token->type == WORD)
			counts[0]++;
		else if (current_token->type == RDIR_OUT)
			counts[1]++;
		else if (current_token->type == RDIR_APPEND)
			counts[2]++;
		current_token = current_token->next;
	}
}

t_tree	*handle_pipe(t_tree *root, t_tree **current, t_tree *pipe_node)
{
	if (root->type != PIPE)
	{
		pipe_node->left = root;
		root = pipe_node;
		*current = root;
	}
	else if ((*current)->right != NULL)
	{
		pipe_node->left = (*current)->right;
		(*current)->right = pipe_node;
		*current = pipe_node;
	}
	else
	{
		(*current)->right = pipe_node;
		*current = pipe_node;
	}
	return (root);
}

t_tree	*handle_rdir(t_tree **current, t_token *token)
{
	if (token->type == RDIR_IN)
		(*current)->in = ft_strdup(token->next->value);
	else if (token->type == RDIR_HEREDOC)
		(*current)->limit = ft_strdup(token->next->value);
	return (*current);
}

t_tree	*handle_non_pipe(t_tree **current, t_tree *new_node)
{
	if ((*current)->right == NULL)
		(*current)->right = new_node;
	else
	{
		(*current)->right->right = new_node;
		*current = new_node;
	}
	return (*current);
}
