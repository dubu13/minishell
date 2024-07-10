/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:12:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/10 19:45:44 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*create_node(t_token *token)
{
	t_tree	*node;
	int		counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	node = initialize_node(token);
	if (!node)
		error(E_ALLOC, NULL);
	if (token->type == CMD)
	{
		count_tokens(token, counts);
		node->cmd = create_cmd_array(token, counts[0]);
		if (!node->cmd)
			error(E_ALLOC, NULL);
	}
	if (counts[1] > 0)
		node->out = create_out_array(token, counts[1]);
	if (counts[2] > 0)
		node->append = create_append_array(token, counts[2]);
	return (node);
}

t_tree	*process_token(t_tree *root, t_tree **current, t_token *token)
{
	t_tree	*new_node;
	t_tree	*pipe_node;

	new_node = create_node(token);
	if (!root)
	{
		root = new_node;
		*current = root;
	}
	else if (token->type == PIPE)
	{
		pipe_node = create_node(token);
		root = handle_pipe(root, current, pipe_node);
	}
	else if (token->type == RDIR_HEREDOC || token->type == RDIR_IN)
		*current = handle_rdir(current, token);
	else if (token->type == CMD)
		*current = handle_non_pipe(current, new_node);
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
		if (token->type == CMD || token->type == PIPE
			|| token->type == RDIR_APPEND || token->type == RDIR_HEREDOC
			|| token->type == RDIR_IN || token->type == RDIR_OUT)
		{
			root = process_token(root, &current, token);
			if (!root)
				error(E_ALLOC, NULL);
		}
		token = token->next;
	}
	return (root);
}
