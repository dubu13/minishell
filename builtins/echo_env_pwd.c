/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_env_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:39:30 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/07 05:32:50 by dkremer          ###   ########.fr       */
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

void	ft_echo(char **input, t_mini *mini)
{
	int		i;
	int		option;
	bool	flag;

	i = 0;
	flag = false;
	option = check_n(input[i]);
	while (input[i] && check_n(input[i]))
		i++;
	while (input[i])
	{
		if (flag)
		{
			if (printf(" ") == -1)
				mini->exit_status = 1;
		}
		if (printf("%s", input[i]) == -1)
			mini->exit_status = 1;
		flag = true;
		i++;
	}
	if (!option)
		printf("\n");
}

void	ft_env(char **input, t_mini *mini)
{
	int	i;

	i = 0;
	if (input[0])
	{
		ft_putstr_fd("env: too many arguments", 2);
		mini->exit_status = 2;
	}
	while (mini->env[i])
	{
		if (!ft_strchr(mini->env[i], '='))
			i++;
		if (mini->env[i])
			printf("%s\n", mini->env[i]);
		i++;
	}
}

void	ft_pwd(char **cmd, t_mini *mini)
{
	char	cwd[PATH_MAX];

	if (cmd[0])
	{
		ft_putstr_fd("pwd: too many arguments\n", 2);
		mini->exit_status = 2;
	}
	if (!getcwd(cwd, PATH_MAX))
	{
		ft_putstr_fd("pwd: error getting path\n", 2);
		mini->exit_status = 1;
	}
	else
		printf("%s\n", cwd);
}
