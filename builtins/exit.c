/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:11:37 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/19 18:32:31 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
exit status :
0 = success
1 = general errors
2 = misuse of shell builtins, syntax error
126 = command invoked cannot execute
127 = command not found
128 = invalid argument to exit (non numeric)
130 = terminated by ctrl-c
128 + signal number = terminated by signal
*/

int	is_digit(const char *str)
{
	if (str == NULL || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

long long	ft_atoull(const char *str, bool *error)
{
	unsigned long		num;
	int					sign;

	sign = 1;
	num = 0;
	if (!str)
		return (0);
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (*str++ - '0');
	if ((sign == 1 && num > LLONG_MAX)
		|| (sign == -1 && num > 9223372036854775808ULL))
		*error = true;
	return (num * sign);
}

void	ft_exit(char *input, t_mini *mini)
{
	unsigned int	exit_code;
	bool			error;

	printf("exit\n");
	exit_code = mini->exit_status;
	error = false;

	if (input)
	{
		if (*input == '\0')
			exit_code = 0;
		else
		{
			exit_code = ft_atoull(input, &error);
			if ((!is_digit(input) && input) || error)
			{
				builtin_msg(E_EXIT, input);
				exit_code = 255;
			}
		}
	}
	free_mini(mini);
	rl_clear_history();
	exit((unsigned char)exit_code);
}
