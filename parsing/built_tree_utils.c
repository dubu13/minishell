/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:55:23 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/18 21:51:18 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	count_tokens(t_token *token, int *counts)
{
	t_token	*current_token;

	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == CMD || current_token->type == WORD)
		{
			if (current_token->type == RDIR_OUT || \
					current_token->type == RDIR_IN || \
					current_token->type == RDIR_APPEND || \
					current_token->type == RDIR_HEREDOC)
				break ;
			counts[0]++;
		}
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

t_token	*find_token(t_token *token, t_token_type type)
{
	while (token->next)
	{
		if (token->type == type)
			return (token);
		token = token->next;
	}
	return (NULL);
}

void	handle_rdir(t_tree *node, t_token *token)
{
	t_token	*found_token;

	if (!token)
		return ;
	found_token = find_token(token, RDIR_IN);
	if (found_token && found_token->next)
		node->in = ft_strdup(found_token->next->value);
	found_token = find_token(token, RDIR_HEREDOC);
	if (found_token && found_token->next)
		node->limit = ft_strdup(found_token->next->value);
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
