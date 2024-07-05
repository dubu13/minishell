
#include "../minishell.h"

void	handle_env_var(t_mini *mini)
{
	t_token	*current;
	char	*value;

	current = mini->token_list;
	value = NULL;
	while (current)
	{
		current->value = remove_quotes(current->value);
		if (current->value[0] == '$' && current->value[1] == '?')
		{
			//free(current->value);
			//current->value = ft_itoa(mini->exit_status);
		}
		if (current->value[0] == '$' && current->value[1] != '\0')
		{
			value = get_env(mini->env, current->value + 1);
			if (value)
			{
				// free(current->value);
				current->value = ft_strdup(value);
			}
		}
		current = current->next;
	}
}

void	parse(t_mini *mini)
{
	t_token	*tmp;

	mini->input = get_input(mini);
	if (!is_str_closed(mini->input))
		error(E_SYNTAX, NULL);
	else
	{
		tokenize(mini->input, &mini->token_list);
		handle_env_var(mini);
		tmp = mini->token_list;
		mini->binary_tree = build_tree(&tmp);
		//execute_tree(mini->binary_tree, mini);
	}
}
