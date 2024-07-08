/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:11:37 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/08 17:56:56 by dkremer          ###   ########.fr       */
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

void	ft_exit(char **input, t_mini *mini)
{
	unsigned int	exit_code;
	bool			error;

	printf("exit\n");
	exit_code = mini->exit_status;
	error = false;
	if (input)
	{
		if (input[1])
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			exit_code = 1;
		}
		exit_code = ft_atoull(input[0], &error);
		if ((!is_digit(input[0]) && input[0]) || error)
		{
			builtin_msg(E_EXIT, input[0]);
			exit_code = 255;
		}
	}
	free_mini(mini);
	rl_clear_history();
	exit((unsigned char)exit_code);
}
