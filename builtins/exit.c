/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:11:37 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/01 21:01:18 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//exit can be called with no arguments, with a single numeric argument
//9223372036854775807
//-9223372036854775808
void	ft_exit(t_token *input)
{
	unsigned int	exit_code;

	// if (!input)
	// 	printf("exit\n");
	printf("exit\n");
	exit_code = 0;
	if (input)
	{
		if (input->next != NULL)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit_code = 1;
		}
		if (!is_digit(input->value) && input->value)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(input->value, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit_code = 255;
		}
		exit_code = ft_atou(input->value);
	}
	//free stuff
	rl_clear_history();
	exit((unsigned char)exit_code);
}

int	is_digit(const char *str)
{
	int	i;
	long long	num;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	num = ft_atou(str);
	if (num > 9223372036854775807LL || num < -9223372036854775807LL - 1)
		return (0);
	// i = 0;
	// sign = 0;
	// while (str[i] != '\0')
	// {
	// 	while (str[i] == '-' || str[i] == '+' || str[i] == '0')
	// 		i++;
	// 	while (str[i] >= '0' && str[i] <= '9')
	// 	{
	// 		i++;
	// 		sign++;
	// 	}
	// }
	// if (sign >= 20)
		// return (0);
	return (1);
}

long long	ft_atou(const char *str)
{
	int				sign;
	long long		num;

	sign = 1;
	num = 0;
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		num = (num * 10) + (*str++ - '0');
	return (num * sign);
}
