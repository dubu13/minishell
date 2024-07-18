/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:12:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/18 16:34:52 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_node(t_mini *mini, t_token *token, t_tree *node, int *counts)
{
	node->cmd = create_cmd_array(token, counts[0], 0);
	if (!node->cmd)
		msg_for_cmd_node(node, mini);
	if (counts[1] > 0)
	{
		node->out = create_out_array(token, counts[1]);
		if (!node->out)
			msg_for_cmd_node(node, mini);
	}
	if (counts[2] > 0)
	{
		node->append = create_append_array(token, counts[2]);
		if (!node->append)
			msg_for_cmd_node(node, mini);
	}
	if (find_token(token, RDIR_IN) || find_token(token, RDIR_HEREDOC))
		handle_rdir(node, token);
}

t_tree	*create_node(t_mini *mini, t_token *token)
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
		cmd_node(mini, token, node, counts);
	return (node);
}

void	add_front(t_token **lst, t_token *new)
{
	new->next = *lst;
	*lst = new;
}

t_tree	*process_token(t_mini *mini, \
	t_tree *root, t_tree **current, t_token *token)
{
	t_tree	*new_node;
	t_tree	*pipe_node;
	t_token	*empty_token;

	empty_token = NULL;
	if ((token->type == RDIR_IN || token->type == RDIR_OUT || \
				token->type == RDIR_APPEND || token->type == RDIR_HEREDOC) \
					&& !token->prev)
	{
		empty_token = create_token(CMD, "");
		add_front(&token, empty_token);
		token = empty_token;
	}
	if (token->type == CMD)
	{
		new_node = create_node(mini, token);
		if (!new_node)
			return (error(E_ALLOC, NULL), NULL);
		if (empty_token)
		{
			free(empty_token->value);
			free(empty_token);
		}
	}
	if (!root)
	{
		root = new_node;
		*current = root;
	}
	else if (token->type == PIPE)
	{
		pipe_node = create_node(mini, token);
		if (!pipe_node)
			return (free_binary(root), error(E_ALLOC, NULL), NULL);
		root = handle_pipe(root, current, pipe_node);
	}
	else if (token->type == CMD)
		*current = handle_non_pipe(current, new_node);
	return (root);
}

t_tree	*build_tree(t_mini *mini, t_token **tokens)
{
	t_tree	*root;
	t_tree	*current;
	t_token	*token;
	t_token *check;

	if (!*tokens)
		return (NULL);
	root = NULL;
	token = *tokens;
	check = token;
	while (check)
	{
		if ((check->type == RDIR_IN || check->type == RDIR_HEREDOC ||
			check->type == RDIR_OUT || check->type == RDIR_APPEND) && !check->next)
		{
			error(E_SYNTAX, "near unexpected token 'newline'");
			mini->exit_status = 258;
			return (NULL);
		}
		check = check->next;
	}
	while (token)
	{
		if ((!token->prev || !token->next) && token->type == PIPE)
		{
			error(E_SYNTAX, "near unexpected token '|'");
			mini->exit_status = 258;
			return (NULL);
		}
		root = process_token(mini, root, &current, token);
		if (!root)
			return (free_binary(root), error(E_ALLOC, NULL), NULL);
		token = token->next;
	}
	return (root);
}