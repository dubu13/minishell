/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:11:37 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/02 18:21:28 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_token *input)
{
	unsigned int	exit_code;
	bool			error;

	printf("exit\n");
	exit_code = 0;
	error = false;
	if (input)
	{
		if (input->next != NULL)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			exit_code = 1;
		}
		exit_code = ft_atoull(input->value, &error);
		if ((!is_digit(input->value) && input->value) || error)
		{
			builtin_msg(E_EXIT, input->value);
			exit_code = 255;
		}
	}
	//free stuff
	rl_clear_history();
	exit((unsigned char)exit_code);
}

int	is_digit(const char *str)
{
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
