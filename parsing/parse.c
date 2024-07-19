/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:15:45 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/19 19:39:06 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*expander(char **temp, char *new_value, t_mini *mini, t_token *token)
{
	(void)token;
	if (**temp == '\'')
		new_value = handle_single_quote(temp, new_value);
	else if (**temp == '\"')
		new_value = handle_double_quote(temp, new_value, mini);
	else if (**temp == '$' && *(*temp + 1) != '\0')
		new_value = handle_env_expansion(temp, new_value, mini);
	else if (**temp == '\\')
		new_value = handle_backslash(temp, new_value);
	else
		new_value = handle_regular_char(temp, new_value);
	return (new_value);
}

void	process_token_value(t_token *token, t_mini *mini)
{
	char	*new_value;
	char	*temp;

	new_value = ft_strdup("");
	temp = token->value;
	while (*temp)
		new_value = expander(&temp, new_value, mini, token);
	free(token->value);
	token->value = new_value;
}

void	handle_env_var(t_mini *mini)
{
	t_token	*current;

	current = mini->token_list;
	while (current)
	{
		process_token_value(current, mini);
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
	{
		free(mini->input);
		return ;
	}
	if (!is_str_closed(mini->input))
	{
		mini->exit_status = 1;
		error(E_SYNTAX, mini->input);
	}
	else
	{
		tokenize(mini->input, &mini->token_list);
		tmp = mini->token_list;
		handle_env_var(mini);
		mini->binary_tree = build_tree(mini, &tmp);
		free_token_list(&mini->token_list);
		exec_node(mini->binary_tree, mini);
		if (mini->input)
			free(mini->input);
	}
}
