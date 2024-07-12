/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:31:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/10 17:24:51 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char *env, t_mini *mini)
{
	char	*key;
	int		i;

	i = 0;
	if (!ft_isalpha(env[i]) && env[i] != '_')
	{
		builtin_msg(E_EXPORT, env);
		mini->exit_status = 1;
	}
	while (env[i] && env[i] != '=' && !(env[i] == '+' && env[i + 1] == '='))
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
		{
			builtin_msg(E_EXPORT, env);
			mini->exit_status = 1;
		}
		i++;
	}
	key = ft_substr(env, 0, i);
	return (key);
}

void	handle_plus(t_mini *mini, char *key, char *env, int index)
{
	char	*value;

	value = NULL;
	if (index != -1)
	{
		value = get_env(mini->env, key);
		value = ft_strjoin(value, ft_strchr(env, '=') + 1);
		update_env(key, value, mini);
	}
	else
	{
		value = ft_strjoin(key, ft_strchr(env, '+') + 1);
		mini->env = new_env(mini->env, value);
	}
	free(value);
}

void	export_w_arg(char *key, char *env, t_mini *mini)
{
	int		index;

	index = index_env(key, mini->env);
	if ((ft_strchr(env, '+') && *(ft_strchr(env, '+') + 1) == '='))
		handle_plus(mini, key, env, index);
	else
	{
		if (index != -1)
		{
			if (ft_strchr(env, '='))
				update_env(key, ft_strchr(env, '=') + 1, mini);
			else
				update_env(key, NULL, mini);
		}
		else
			mini->env = new_env(mini->env, env);
	}
}

void	export_print(char **env)
{
	char	*quoted_env;
	int		i;

	i = -1;
	env = sort_env(env);
	while (env[++i])
	{
		quoted_env = put_quotes(env[i]);
		printf("declare -x %s\n", quoted_env);
		free(quoted_env);
		free(env[i]);
		env[i] = NULL;
	}
}

void	ft_export(char **input, t_mini *mini)
{
	char	*key;
	int		i;

	i = -1;
	mini->exit_status = 0;
	if (!input[0])
		export_print(mini->env);
	while (input[++i])
	{
		key = get_key(input[i], mini);
		export_w_arg(key, input[i], mini);
		free(key);
	}
}
