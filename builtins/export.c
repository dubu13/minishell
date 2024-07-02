/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 18:31:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/02 18:19:25 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Extracts the key from an environment variable string.
 *
 * This function takes an environment variable string in the format "KEY=VALUE"
 * or "KEY+=VALUE" and extracts the key portion. It first checks that the first
 * character of the string is a valid identifier character (alphabetic or
 * underscore). It then iterates through the string, checking that each
 * character is a valid identifier character (alphanumeric or underscore), until
 * it reaches the '=' or '+=' separator. The function then returns a newly
 * allocated string containing the extracted key.
 *
 * @param env The environment variable string in the format "KEY=VALUE" or
 *            "KEY+=VALUE".
 * @return A newly allocated string containing the extracted key.
 */
char	*get_key(char *env)
{
	char	*key;
	int		i;

	i = 0;
	if (!ft_isalpha(env[i]) && env[i] != '_')
		builtin_msg(E_EXPORT, env);
	while (env[i] && env[i] != '=' && !(env[i] == '+' && env[i + 1] == '='))
	{
		if (!ft_isalnum(env[i]) && env[i] != '_')
			builtin_msg(E_EXPORT, env);
		i++;
	}
	key = ft_substr(env, 0, i);
	return (key);
}

/**
 * Updates the environment with a new key-value pair or appends a value to an
 * existing key.
 *
 * This function takes a key, an environment variable string, and the Minishell
 * program context as parameters. It first checks if the environment variable
 * string contains a '+' character, which indicates that the value should be
 * appended to the existing value for the given key.
 *
 * If the '+' character is present, the function retrieves the existing value
 * for the key and appends the new value to it. If the key does not exist in the
 * environment, the function creates a new environment variable with the
 * provided key-value pair.
 *
 * If the '+' character is not present, the function checks if the key already
 * exists in the environment. If it does, the function updates the value for the
 * existing key. If the key does not exist, the function creates a new
 * environment variable with the provided key-value pair.
 *
 * @param key The key for the environment variable.
 * @param env The environment variable string in the format "KEY=VALUE".
 * @param mini The Minishell program context.
 */

void	handle_plus(t_mini *mini, char *key, char *env, int index)
{
	char	*value;

	if (index != -1)
	{
		value = get_env(mini->env, key);
		value = ft_strjoin(value, ft_strchr(env, '=') + 1);
		update_env(key, value, mini);
		free(value);
	}
	else
	{
		value = ft_strjoin(key, ft_strchr(env, '+') + 1);
		mini->env = new_env(mini->env, value);
	}
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

/**
 * Prints the current environment variables in a formatted way.
 *
 * This function takes an array of environment variables `env` and prints each
 * variable in the format "declare -x KEY="VALUE"". The environment variables
 * are first sorted alphabetically using the `sort_env` function, and then
 * each variable is quoted using the `put_quotes` function before being printed.
 *
 * @param env An array of environment variables to be printed.
 */
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

/**
 * Handles the 'export' builtin command in the Minishell program.
 *
 * If the 'input' parameter is NULL or its type is not WORD, the function
 * prints the current environment variables using the 'export_print' function.
 *
 * Otherwise, the function iterates through the 'input' tokens of type WORD,
 * extracts the key from each token using the 'get_key' function, and then
 * calls the 'export_w_arg' function to update the environment with the
 * provided key-value pair.
 *
 * After processing all the input tokens, the function calls 'export_print'
 * again to display the updated environment variables.
 *
 * @param input The linked list of tokens representing the 'export' command.
 * @param mini The Minishell program context.
 */
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
}
