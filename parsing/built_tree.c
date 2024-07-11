/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:12:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/11 20:13:52 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_node(t_token *token, t_tree *node, int *counts)
{
	node->cmd = create_cmd_array(token, counts[0]);
	if (!node->cmd)
	{
		free_binary(node);
		error(E_ALLOC, NULL);
	}
	if (counts[1] > 0)
	{
		node->out = create_out_array(token, counts[1]);
		if (!node->out)
		{
			free_binary(node);
			error(E_ALLOC, NULL);
		}
	}
	if (counts[2] > 0)
	{
		node->append = create_append_array(token, counts[2]);
		if (!node->append)
		{
			free_binary(node);
			error(E_ALLOC, NULL);
		}
	}
	else
		handle_rdir(node, token);
}

t_tree	*create_node(t_token *token)
{
	t_tree	*node;
	int		counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	node = initialize_node(token);
	if (!node)
		return (error(E_ALLOC, NULL), NULL);
	count_tokens(token, counts);
	if (token->type == CMD)
		cmd_node(token, node, counts);
	return (node);
}

t_tree	*process_token(t_tree *root, t_tree **current, t_token *token)
{
	t_tree	*new_node;
	t_tree	*pipe_node;

	if (token->type == CMD)
	{
		new_node = create_node(token);
		if (!new_node)
			return (error(E_ALLOC, NULL), NULL);
	}
	if (!root)
	{
		root = new_node;
		*current = root;
	}
	else if (token->type == PIPE)
	{
		pipe_node = create_node(token);
		if (!pipe_node)
			return (free_binary(root), error(E_ALLOC, NULL), NULL);
		root = handle_pipe(root, current, pipe_node);
	}
/* 	else if (token->type == RDIR_HEREDOC || token->type == RDIR_IN)
		*current = handle_rdir(current, token); */
	else if (token->type == CMD)
	{
		*current = handle_non_pipe(current, new_node);
	}
	return (root);
}

t_tree	*build_tree(t_token **tokens)
{
	t_tree	*root;
	t_tree	*current;
	t_token	*token;

	if (!*tokens)
		return (NULL);
	root = NULL;
	current = NULL;
	token = *tokens;
	while (token)
	{
		root = process_token(root, &current, token);
		if (!root)
			return (free_binary(root), error(E_ALLOC, NULL), NULL);
		token = token->next;
	}
	return (root);
}
