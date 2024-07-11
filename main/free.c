/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:50:06 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/11 18:40:05 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_token_list(t_token **token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list || !*token_list)
		return ;
	current = *token_list;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*token_list = NULL;
}

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->cmd)
	{
		if (tree->cmd)
			free_array(tree->cmd);
		if (tree->in)
			free(tree->in);
		if (tree->out)
			free_array(tree->out);
		if (tree->limit)
			free(tree->limit);
		if (tree->append)
			free_array(tree->append);
	}
	tree->cmd = NULL;
	tree->in = NULL;
	tree->out = NULL;
	tree->limit = NULL;
	tree->append = NULL;
}

void	free_binary(t_tree *tree)
{
	if (!tree)
		return;
	if (tree->type == PIPE)
	{
		free_binary(tree->left);
		free(tree->left);
		tree->left = NULL;
		free_binary(tree->right);
		free(tree->right);
		tree->right = NULL;
	}
	else
	{
		free_tree(tree);
	}
}

void	free_mini(t_mini *mini)
{
	if (mini)
	{
		if (mini->env)
		{
			free_array(mini->env);
			mini->env = NULL;
		}
		if (mini->input)
			free(mini->input);
		if (mini->token_list)
			free_token_list(&(mini->token_list));
		if (mini->binary_tree)
		{
			free_binary(mini->binary_tree);
			free(mini->binary_tree);
		}
		free(mini);
	}
}
