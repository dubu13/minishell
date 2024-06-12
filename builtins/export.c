/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:31:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/12 22:44:21 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
//lets say args[0] = export
//args[1] = NAME=VALUE
//change the params

char	*get_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	if (!ft_isalpha(env[i]) && env[i] != '_')
		error(E_EXPORT);
	while (env[i] && env[i] != '=')
	{
		if ((!ft_isalnum(env[i]) && env[i] != '_') && (env[i] != '+'
				&& env[i + 1] != '='))
			error(E_EXPORT);
		i++;
	}
	key = ft_substr(env, 0, i);
	return (key);
}

void	export_w_arg(char *key, char *env, t_mini *mini)
{
	char	*exist_env;
	int		index;

	index = index_env(key, mini->env);
	if ((ft_strchr(env, '+') && ft_strchr(env, '=')) == ft_strchr(env, '+') + 1)
	{
		if (index != -1)
		{
			exist_env = get_env(mini->env, key);
			mini->env[index] = ft_strjoin(exist_env, ft_strchr(env, '=') + 1);
			free(exist_env);
		}
	}
	else
	{
		if (index != -1)
			update_env(key, ft_strchr(env, '=') + 1, mini);
		else
			mini->env = new_env(mini->env, env);
	}
}

void	export_print(char **env)
{
	int		i;
	char	*quoted_env;

	i = 0;
	env = sort_env(*env);
	while (env[i])
	{
		quoted_env = put_quotes(env[i]);
		printf("declare -x %s\n", quoted_env);
		i++;
	}
}

void	ft_export(char **args, t_mini *mini)
{
	char	*key;
	int		i;

	i = 1;
	while (args[i])
	{
		if (args[i] == NULL)
			export_print(mini->env);
		else
		{
			key = get_key(args[i]);
			export_w_arg(key, args[i], mini);
		}
		i++;
	}
}
