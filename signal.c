/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:15:13 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/28 14:21:13 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles signals received by the program.
 *

	* This function is called when a SIGINT (Ctrl+C) or SIGQUIT (Ctrl+\) signal is received.
 * For SIGINT, it writes "^C" to the standard output.
 * For SIGQUIT, it writes "Quit: 3" to the standard output,
	moves the cursor to a new line, and writes a carriage return.
 *
 * @param sig The signal number that was received.
 */
void	sig_action(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// else if (sig == SIGQUIT)
	// {
	// 	write(1, "Quit: 3\n", 8);
	// 	rl_on_new_line();
	// 	write(1, "\r", 1);
	// }
}

void	handle_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sig_action);
	signal(SIGQUIT, SIG_IGN);
}
