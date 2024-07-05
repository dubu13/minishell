/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:14:50 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/05 17:44:23 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
exit status :
0 = success
1 = general errors
2 = misuse of shell builtins
126 = command invoked cannot execute
127 = command not found
128 = invalid argument to exit (non numeric)
130 = terminated by ctrl-c
128 + signal number = terminated by signal

*/

void	exec_command(char **cmd, t_mini *mini)
{
	if (check_builtin(cmd[0]))
		exec_builtin(cmd, mini);
	else
		external_command(cmd, mini);
}
