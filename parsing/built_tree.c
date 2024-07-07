/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:12:58 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/07 12:44:50 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tree	*create_node(t_token *token)
{
	t_tree	*node;
	int		cmd_count;
	int		out_count;
	int		append_count;
	t_token	*current_token;

	node = initialize_node(token);
	if (!node)
		error(E_ALLOC, NULL);
	out_count = 0;
	append_count = 0;
	if (token->type == CMD)
	{
		cmd_count = 0;
		current_token = token;
		while (current_token && current_token->type != PIPE)
		{
			if (current_token->type == CMD || current_token->type == WORD)
				cmd_count++;
			else if (current_token->type == RDIR_OUT)
				out_count++;
			else if (current_token->type == RDIR_APPEND)
				append_count++;
			current_token = current_token->next;
		}
		node->cmd = create_cmd_array(token, cmd_count);
		if (!node->cmd)
		{
			free(node);
			error(E_ALLOC, NULL);
		}
	}
	if (out_count > 0)
		node->out = create_out_array(token, out_count);
	if (append_count > 0)
		node->append = create_append_array(token, append_count);
	return (node);
}

t_tree	*initialize_node(t_token *token)
{
	t_tree	*node;

	node = ft_calloc(sizeof(t_tree), 1);
	if (!node)
		return (NULL);
	node->type = token->type;
	return (node);
}

char	**create_cmd_array(t_token *token, int cmd_count)
{
	char	**cmd_array;
	t_token	*current_token;
	int		i;

	cmd_array = ft_calloc(sizeof(char *), (cmd_count + 1));
	if (!cmd_array)
		error(E_ALLOC, NULL);
	i = 0;
	current_token = token;
	while (current_token && current_token->type != PIPE
		&& (current_token->type == WORD || current_token->type == CMD))
	{
		cmd_array[i++] = ft_strdup(current_token->value);
		current_token = current_token->next;
	}
	cmd_array[i] = NULL;
	return (cmd_array);
}

char	**create_out_array(t_token *token, int out_count)
{
	char	**out_array;
	t_token	*current_token;
	int		i;

	i = 0;
	out_array = ft_calloc(sizeof(char *), (out_count + 1));
	if (!out_array)
		error(E_ALLOC, NULL);
	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == RDIR_OUT)
			out_array[i++] = ft_strdup(current_token->next->value);
		current_token = current_token->next;
	}
	out_array[i] = NULL;
	return (out_array);
}

char	**create_append_array(t_token *token, int append_count)
{
	char	**append_array;
	t_token	*current_token;
	int		i;

	i = 0;
	append_array = ft_calloc(sizeof(char *), (append_count + 1));
	if (!append_array)
		error(E_ALLOC, NULL);
	current_token = token;
	while (current_token && current_token->type != PIPE)
	{
		if (current_token->type == RDIR_APPEND)
			append_array[i++] = ft_strdup(current_token->next->value);
		current_token = current_token->next;
	}
	append_array[i] = NULL;
	return (append_array);
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
