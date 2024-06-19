/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:39:30 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 15:21:33 by dhasan           ###   ########.fr       */
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

int	ft_echo(t_token *input)
{
	int		option;
	bool	flag;

	flag = false;
	option = check_n(input->value);
	while (input && check_n(input->value))
		input = input->next;
	while (input && input->type == WORD)
	{
		if (flag)
		{
			if (printf(" ") == -1)
				return (EXIT_FAILURE);
		}
		if (printf("%s", input->value) == -1)
			return (EXIT_FAILURE);
		flag = true;
		input = input->next;
	}
	if (!option)
		printf("\n");
	return (0);
}

void	ft_env(t_token *input, t_mini *mini)
{
	int		i;

	i = 0;
	while (input && input->type == WORD)
	{
		i++;
		input = input->next;
	}
	if (i != 0)
		error(E_SYNTAX, "too many arguments");
	else
	{
		i = 0;
		while (mini->env[i])
		{
			printf("%s\n", mini->env[i]);
			i++;
		}

	}
}

int	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
	else
		return (EXIT_FAILURE);
	return (0);
}
