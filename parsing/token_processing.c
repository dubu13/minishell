/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 22:38:04 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/18 22:38:18 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_token	*handle_redirection(t_token **token)
{
	t_token	*empty_token;

	empty_token = NULL;
	if (((*token)->type >= RDIR_IN && (*token)->type <= RDIR_HEREDOC) \
			&& !(*token)->prev)
	{
		empty_token = create_token(CMD, "");
		add_front(token, empty_token);
		*token = empty_token;
	}
	return (empty_token);
}

static t_tree	*create_cmd_node(t_mini *mini, t_token *token, \
			t_token *empty_token)
{
	t_tree	*new_node;

	new_node = create_node(mini, token);
	if (!new_node)
		return (error(E_ALLOC, NULL), NULL);
	if (empty_token)
	{
		free(empty_token->value);
		free(empty_token);
	}
	return (new_node);
}

static t_tree	*handle_pipe_node(t_mini *mini, t_tree *root, \
				t_tree **current, t_token *token)
{
	t_tree	*pipe_node;

	pipe_node = create_node(mini, token);
	if (!pipe_node)
		return (free_binary(root), error(E_ALLOC, NULL), NULL);
	return (handle_pipe(root, current, pipe_node));
}

t_tree	*process_token(t_mini *mini, t_tree *root, \
			t_tree **current, t_token *token)
{
	t_tree	*new_node;
	t_token	*empty_token;

	new_node = NULL;
	empty_token = handle_redirection(&token);
	if (token->type == CMD)
		new_node = create_cmd_node(mini, token, empty_token);
	if (!root)
	{
		root = new_node;
		*current = root;
	}
	else if (token->type == PIPE)
		root = handle_pipe_node(mini, root, current, token);
	else if (token->type == CMD)
		*current = handle_non_pipe(current, new_node);
	return (root);
}
