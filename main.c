/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/05 19:27:00 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tree_vertical(t_tree *node, int level, char *side)
{
	 if (node == NULL)
			 return;

	// Print the current node
	printf("%s: ", side);
	if (node->type == PIPE)
			printf("PIPE\n");
	else if (node->cmd != NULL)
	{
			printf("WORD: ");
			for (int i = 0; node->cmd[i] != NULL; i++)
					printf("%s ", node->cmd[i]);
			printf("\n");
	}
	else
			printf("REDIRECT\n");
	 // Process children with increased level
	 print_tree_vertical(node->left, level + 1, "L");
	 print_tree_vertical(node->right, level + 1, "R");
}

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (perror("Malloc"), NULL);
	mini->env = save_env();
	mini->input = NULL;
	mini->exit_status = 0;
	mini->token_list = NULL;
	mini->binary_tree = NULL;
	return (mini);
}

int	main(void)
{
	t_mini	*mini;

	mini = init_mini();
	if (!mini)
		return (EXIT_FAILURE);
	while (1)
	{
		parse(mini);
		print_tree_vertical(mini->binary_tree, 0, "root");
		if (!mini->input)
		{
			printf("exit\n");
			break ;
		}
		free_token_list(mini->token_list);
		//free_tree(mini->binary_tree);
		mini->token_list = NULL;
		//mini->binary_tree = NULL;
	}
	rl_clear_history();
	free_mini(mini);
	return (0);
}
