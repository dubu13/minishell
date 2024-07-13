/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:15:45 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 02:14:34 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_env_var(t_mini *mini)
{
    t_token *current = mini->token_list;
    while (current)
    {
        char *new_value = ft_strdup("");
        char *temp = current->value;
        while (*temp)
        {
            if (*temp == '\'')
                new_value = handle_single_quote(&temp, new_value);
            else if (*temp == '\"')
                new_value = handle_double_quote(&temp, new_value, mini);
            else if (*temp == '$' && *(temp + 1) != '\0')
                new_value = handle_env_expansion(&temp, new_value, mini);
            else if (*temp == '\\')
                new_value = handle_backslash(&temp, new_value);
            else
                new_value = handle_regular_char(&temp, new_value);
        }
        free(current->value);
        current->value = new_value;
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
