/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:15:13 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/07 05:31:15 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
