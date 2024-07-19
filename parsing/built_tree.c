/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:12:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/19 17:44:16 by dhasan           ###   ########.fr       */
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
	if (counts[3] > 0)
	{
		node->in = create_in_array(token, counts[3]);
		if (!node->in)
			msg_for_cmd_node(node, mini);
	}
	if (find_token(token, RDIR_HEREDOC))
		handle_rdir(node, token);
}

t_tree	*create_node(t_mini *mini, t_token *token)
{
	t_tree	*node;
	int		counts[4];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	node = initialize_node(token);
	if (!node)
		return (error(E_ALLOC, NULL), NULL);
	count_tokens(token, counts);
	if (token->type == CMD)
		cmd_node(mini, token, node, counts);
	return (node);
}

static int	check_syntax(t_token *token, t_mini *mini)
{
	while (token)
	{
		if ((token->type >= RDIR_IN && token->type <= RDIR_APPEND) \
				&& !token->next)
		{
			error(E_SYNTAX, "near unexpected token 'newline'");
			mini->exit_status = 258;
			return (0);
		}
		if ((!token->prev || !token->next) && token->type == PIPE)
		{
			error(E_SYNTAX, "near unexpected token '|'");
			mini->exit_status = 258;
			return (0);
		}
		token = token->next;
	}
	return (1);
}

t_tree	*build_tree(t_mini *mini, t_token **tokens)
{
	t_tree	*root;
	t_tree	*current;
	t_token	*token;

	if (!*tokens)
		return (NULL);
	if (!check_syntax(*tokens, mini))
		return (NULL);
	root = NULL;
	token = *tokens;
	while (token)
	{
		root = process_token(mini, root, &current, token);
		if (!root)
			return (free_binary(root), error(E_ALLOC, NULL), NULL);
		token = token->next;
	}
	return (root);
}
