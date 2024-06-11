/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:57:05 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/11 17:09:20 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char *args)
{
	int	i;

	if (!args || args[0] != '-')
		return (0);
	i = 1;
	while (args[i] == 'n')
		i++;
	return (args[i] == '\0');
}

int	ft_echo(char **args)
{
	int		option;
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	option = check_n(args[i]);
	while (args[i] && check_n(args[i]))
		i++;
	while (args[i])
	{
		if (flag)
		{
			if (printf(" ") == -1)
				return (EXIT_FAILURE);
		}
		if (printf("%s", args[i]) == -1)
			return (EXIT_FAILURE);
		flag = true;
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
