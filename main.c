/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/05 18:04:18 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tree_vertical(t_tree *node, int level, char *side)
{
    if (node == NULL)
        return;

    // Print indentation for the current level
    for (int i = 0; i < level; i++)
        printf("    "); // 4 spaces per level for better readability

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


void	parse(t_mini *mini)
{
	t_token	*tmp;

	mini->input = get_input(mini);
	if (!is_str_closed(mini->input))
		error(E_SYNTAX, NULL);
	else
	{
		tokenize(mini->input, &mini->token_list);
		tmp = mini->token_list;
		mini->binary_tree = build_tree(&tmp);
		print_tree_vertical(mini->binary_tree, 0, "root");
		// execute_tree(mini->binary_tree, mini);
	}
}

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (perror("Malloc"), NULL);
	mini->env = save_env();
	mini->input = NULL;
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
	//free everything
	return (0);
}
