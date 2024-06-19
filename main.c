/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 16:14:36 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse(t_mini *mini)
{
	mini->input = get_input(mini);
	if (!is_str_closed(mini->input))
		error(E_SYNTAX, NULL);
	else
		tokenize(mini->input, &mini->token_list);
	exec_builtin(mini);
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
	return (mini);
}

int	main(void)
{
	t_mini	*mini;

	mini = init_mini();
	while (1)
		parse(mini);
}
