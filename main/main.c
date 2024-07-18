/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/18 20:17:02 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**save_env(void)
{
	extern char	**environ;
	char		**env;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	env = ft_calloc(i + 1, sizeof(char *));
	if (!env)
		return (error(E_ALLOC, NULL), NULL);
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		if (!env[i])
			return (error(E_ALLOC, NULL), NULL);
		i++;
	}
	return (env);
}

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
		handle_signal();
		parse(mini);
		if (!mini->input)
			break ;
		free_binary(mini->binary_tree);
		free(mini->binary_tree);
		mini->binary_tree = NULL;
	}
	rl_clear_history();
	free_mini(mini);
	return (0);
}
