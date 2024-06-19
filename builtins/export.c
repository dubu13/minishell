/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:31:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 17:17:46 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
// can get multi args
//lets say args[0] = export
//args[1] = NAME=VALUE
//change the params

char	*get_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	if (!ft_isalpha(env[i]) && env[i] != '_')
		error(E_EXPORT, env);
	while (env[i] && (env[i] != '=' || env[i] != '+'))
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
			error(E_EXPORT, env);
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
	if ((ft_strchr(env, '+') && *(ft_strchr(env, '+') + 1) == '='))
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
	env = sort_env(env);
	while (env[i])
	{
		quoted_env = put_quotes(env[i]);
		printf("declare -x %s\n", quoted_env);
		i++;
	}
}

void	ft_export(t_token *input, t_mini *mini)
{
	char	*key;

	if (input == NULL || input->type != WORD)
		export_print(mini->env);
	while (input && input->type == WORD)
	{
		key = get_key(input->value);
		export_w_arg(key, input->value, mini);
		input = input->next;
	}
	printf("---------------after export---------------\n");
	export_print(mini->env);
}
