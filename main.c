/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/23 19:00:24 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	//initialize

	//handle signals
	//-ctrl-c, ctrl-d, ctrl-\ //

	//display prompt
	//get input

	char	*prompt;

	prompt = readline(CYN "Minishell$ " RED);
	// if (argc > 1)
	// 	ft_echo(argv);

	//for ft_cd
	// use getenv :
	// use getcwd :get the pathname of the current working directory

	// signal(SIGQUIT, &signal_handle);
	// add_history(prompt);

}
