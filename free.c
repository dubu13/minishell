/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 12:50:06 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/05 12:57:18 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token *token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list)
		return ;
	current = token_list;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

void	free_tree(t_tree *tree)
{
	int	i;

	if (tree)
	{
		if (tree->cmd)
		{
			i = 0;
			while (tree->cmd[i])
			{
				free(tree->cmd[i]);
				i++;
			}
			free(tree->cmd);
		}
		free_tree(tree->left);
		free_tree(tree->right);
		free(tree);
	}
}
