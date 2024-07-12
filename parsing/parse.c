/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:15:45 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/12 21:23:12 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	replace_env_var(t_token *current, t_mini *mini)
{
	char	*value;

	value = get_env(mini->env, current->value + 1);
	free(current->value);
	current->value = ft_strdup(value);
	free(value);
}

void	handle_env_var(t_mini *mini)
{
	t_token	*current;

	current = mini->token_list;
	while (current)
	{
		if (current->value[0] == '\'')
		{
			current->value = remove_quotes(current->value);
			current = current->next;
			continue ;
		}
		current->value = remove_quotes(current->value);
		if (current->value[0] == '$' && current->value[1] == '?')
		{
			free(current->value);
			current->value = ft_itoa(mini->exit_status);
		}
		else if (current->value[0] == '$' && current->value[1] != '\0')
			replace_env_var(current, mini);
		current = current->next;
	}
}

void	parse(t_mini *mini)
{
	t_token	*tmp;

	mini->input = get_input(mini);
	if (!mini->input)
	{
		printf("exit\n");
		mini->exit_status = 0;
		return ;
	}
	if (!ft_strncmp(mini->input, "", 1))
		return ;
	if (!is_str_closed(mini->input))
	{
		mini->exit_status = 1;
		error(E_SYNTAX, mini->input);
	}
	else
	{
		tokenize(mini->input, &mini->token_list);
		handle_env_var(mini);
		tmp = mini->token_list;
		mini->binary_tree = build_tree(&tmp);
		free_token_list(&mini->token_list);
		exec_node(mini->binary_tree, mini);
	}
}
