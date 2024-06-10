/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:31:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/10 23:25:51 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//lets say args[0] = export
//args[1] = NAME=VALUE

char	**sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

void	only_export(char **env)
{
	int	i;

	i = 0;
	env = sort_env(*env);
	//add value in double quotes
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}
void	ft_export(char *args, t_mini *mini)
{
	//without arg, print env for export
	//declare -x and put value in double quotes
	if (args[1] == NULL)
		only_export(mini->env);
	//if its with arg, get the NAME
	//check the name
	//should start with a letter or an underscore
	//if there is + before =,
	//check if the variable already exists
	//if it does, append the value else create a new variable
}
