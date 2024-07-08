/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:50:06 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/08 14:11:05 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	i;

	i = -1;
	if (tree)
	{
		if (tree->cmd)
		{
			while (tree->cmd[++i])
				free(tree->cmd[i]);
			free(tree->cmd);
		}
		free_tree(tree->left);
		free_tree(tree->right);
		free(tree);
	}
}

void	free_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	free_mini(t_mini *mini)
{
	if (mini)
	{
		if (mini->env)
			free_array(mini->env);
		if (mini->input)
			free(mini->input);
		if (mini->token_list)
			free_token_list(&(mini->token_list));
		if (mini->binary_tree)
			free_tree(mini->binary_tree);
		free(mini);
	}
}
