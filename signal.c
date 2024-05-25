/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:15:13 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/25 13:38:02 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handle(int sig)
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
