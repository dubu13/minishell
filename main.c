/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/08 17:29:13 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = ft_calloc(sizeof(t_mini), 1);
	if (!mini)
		return (error(E_ALLOC, NULL), NULL);
	mini->env = save_env();
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
		free_token_list(&(mini->token_list));
		mini->token_list = NULL;
		//mini->binary_tree = NULL;
	}
	rl_clear_history();
	free_mini(mini);
	return (0);
}
