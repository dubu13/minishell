/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:15:13 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 16:14:57 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Handles signals received by the program.
 *
 * This function is called when a SIGINT (Ctrl+C) or SIGQUIT (Ctrl+\) signal is received.
 * For SIGINT, it writes "^C" to the standard output.
 * For SIGQUIT, it writes "Quit: 3" to the standard output, moves the cursor to a new line, and writes a carriage return.
 *
 * @param sig The signal number that was received.
 */
void signal_handle(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "^C\n", 3);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		rl_on_new_line();
		write(1, "\r", 1);
	}
}
