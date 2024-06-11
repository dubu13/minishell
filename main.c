/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/11 15:46:31 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_builtin(char *cmd)
// {
// 	// if (!ft_strncmp(cmd, "echo", 4))
// 	// 	return (ft_echo());
// 	// if (!ft_strncmp(cmd, "pwd", 3))
// 	// 	return (ft_pwd());
// 	// if (!ft_strncmp(cmd, "cd", 2))
// 	// 	return (ft_cd());
// 	// if (!ft_strncmp(cmd, "exit", 4))
// 	// 	return ();
// 	// if (!ft_strncmp(cmd, "export", 6))
// 	// 	return ();
// 	// if (!ft_strncmp(cmd, "unset", 5))
// 	// 	return ();
// 	// if (!ft_strncmp(cmd, "env", 3))
// 	// 	return ();
// }

void	parse(t_mini *mini)
{
	mini->input = get_input(mini);
	if (!is_str_closed(mini->input))
		error(E_SYNTAX);
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
	return (mini);
}

int	main(void)
{
	t_mini	*mini;

	mini = init_mini();
	parse(mini);
}
