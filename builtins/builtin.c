/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 22:37:00 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/25 15:48:49 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**

	* Executes the appropriate built-in command based on the tokens in the mini shell.

	* This function iterates through the token list and calls the corresponding built-in
 * function for each recognized command, such as echo, pwd, cd, export, unset,
	and env.

	* The built-in functions are responsible for executing the command and updating the
 * mini shell state as necessary.
 *

	* @param mini The mini shell structure containing the token list and other state.
 */
void	exec_builtin(t_mini *mini)
{
	t_token	*current;

	current = mini->token_list;
	while (current)
	{
		if (!ft_strncmp(current->value, "echo", 4))
			ft_echo(current->next);
		else if (!ft_strncmp(current->value, "pwd", 3))
			ft_pwd();
		else if (!ft_strncmp(current->value, "cd", 2))
			ft_cd(current->next, mini);
		// if (!ft_strncmp(current->value, "exit", 4))
		// 	return ();
		else if (!ft_strncmp(current->value, "export", 6))
			return (ft_export(current->next, mini));
		else if (!ft_strncmp(current->value, "unset", 5))
			return (ft_unset(current->next, mini));
		else if (!ft_strncmp(current->value, "env", 3))
			return (ft_env(current->next, mini));
		current = current->next;
	}
}

int	check_builtin(t_token *input)
{
	if (!ft_strncmp(input->value, "echo", 4))
		return (1);
	else if (!ft_strncmp(input->value, "pwd", 3))
		return (1);
	else if (!ft_strncmp(input->value, "cd", 2))
		return (1);
	else if (!ft_strncmp(input->value, "export", 6))
		return (1);
	else if (!ft_strncmp(input->value, "unset", 5))
		return (1);
	else if (!ft_strncmp(input->value, "env", 3))
		return (1);
	return (0);
}
