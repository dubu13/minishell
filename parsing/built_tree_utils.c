/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 00:55:23 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/07 00:55:32 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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