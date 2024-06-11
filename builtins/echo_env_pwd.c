/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:39:30 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/11 22:39:45 by dhasan           ###   ########.fr       */
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

void	ft_env(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
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
