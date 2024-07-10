
#include "../minishell.h"

void	handle_env_var(t_mini *mini)
{
	t_token	*current;
	char	*value;

	current = mini->token_list;
	value = NULL;
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

void	print_tree(t_tree *node)
{
	if (node == NULL)
		return;
	printf("Type: %d\n", node->type);
	if (node->cmd)
	{
		printf("Command: ");
		for (int i = 0; node->cmd[i]; i++)
			printf("%s ", node->cmd[i]);
		printf("\n");
	}
	if (node->in)
		printf("Input: %s\n", node->in);
	if (node->out)
	{
		printf("Output: ");
		for (int i = 0; node->out[i]; i++)
			printf("%s ", node->out[i]);
		printf("\n");
	}
	if (node->append)
	{
		printf("Append: ");
		for (int i = 0; node->append[i]; i++)
			printf("%s ", node->append[i]);
		printf("\n");
	}
	if (node->limit)
		printf("Limit: %s\n", node->limit);
	print_tree(node->left);
	print_tree(node->right);
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
		print_tree(mini->binary_tree);
		exec_command(mini->binary_tree, mini);
		//execute_tree(mini->binary_tree, mini);
	}
}
