/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/02 15:40:38 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**test(char *input)
{
	char	**test;

	test = ft_split(input, '|');
	return (test);
}

void	parse(t_mini *mini)
{
	t_tree	*root;
	t_token	*tmp;

	mini->input = get_input(mini);
	mini->cmd_list = test(mini->input);
	if (!is_str_closed(mini->input))
		error(E_SYNTAX, NULL);
	else
	{
		tokenize(mini->input, &mini->token_list);
		tmp = mini->token_list;
		root = build_tree(&tmp);
		execute_tree(root, mini);
	}
}

/**
 * Initializes a new t_mini struct, which is the main data structure used in the
 * minishell program.
 *
 * The function allocates memory for the t_mini struct, saves the current
 * environment variables, and initializes the input, token_list, and env
 * members of the struct.
 *
 * @return A pointer to the newly initialized t_mini struct, or NULL if memory
 * allocation failed.
 */
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

void	ft_reset(t_token *list)
{
	t_token	*tmp;

	if (list)
	{
		while (list)
		{
			tmp = list->next;
			free(list);
			list = tmp;
		}
	}
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
		ft_reset(mini->token_list);
		mini->token_list = NULL;
	}
	rl_clear_history();
	return (0);
}
