/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/06 19:10:29 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (!mini->input)
			break ;
		free_token_list(mini->token_list);
		//free_tree(mini->binary_tree);
		mini->token_list = NULL;
		//mini->binary_tree = NULL;
	}
	rl_clear_history();
	free_mini(mini);
	return (0);
}
