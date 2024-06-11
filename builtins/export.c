/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:31:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/11 19:25:13 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
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

char	*put_quotes(char *env)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	key = ft_substr(env, 0, i);
	value = ft_strdup(env + i + 1);
	value = ft_strjoin("\"", value);
	value = ft_strjoin(value, "\"");
	key = ft_strjoin(key, "=");
	env = ft_strjoin(key, value);
	free(key);
	free(value);
	return (env);
}

void	only_export(char **env)
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

void	*check_key(char *key, char *env, t_mini *mini)
{
	int		i;

	if (ft_strchr(env, '+') && ft_strchr(env, '=') == ft_strchr(env, '+') + 1)
}

void	ft_export(char **args, t_mini *mini)
{
	char	*key;

	if (args[1] == NULL)
		only_export(mini->env);
	else
	{
		key = get_key(args[1]);
		check_key(key, args[1], mini);
	}
	//if its with arg, get the NAME
	//check the name
	//should start with a letter or an underscore
	//if there is + before =,
	//check if the variable already exists
	//if it does, append the value else create a new variable
}
