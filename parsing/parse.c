
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

void print_tree_vertical(t_tree *node, int level, const char *side) {
    if (node == NULL)
        return;

    // Print indentation for the current level
    for (int i = 0; i < level; i++)
        printf("    "); // 4 spaces per level for better readability

    // Print the current node
    printf("%s: ", side);
    if (node->type == PIPE)
        printf("PIPE\n");
    else if (node->type == CMD || node->type == WORD)
    {
        printf("WORD: ");
        if (node->cmd) {
            for (int i = 0; node->cmd[i] != NULL; i++)
                printf("%s ", node->cmd[i]);
        } else {
            printf("Unknown Command ");
        }
        printf("\n");
    }
    else if (node->type == RDIR_IN)
        printf("RDIR_IN\n");
    else if (node->type == RDIR_OUT)
        printf("RDIR_OUT\n");
    else if (node->type == RDIR_APPEND)
        printf("RDIR_APPEND\n");
    else if (node->type == RDIR_HEREDOC)
        printf("RDIR_HEREDOC\n");
    else
        printf("UNKNOWN\n");

    // Process children with increased level
    print_tree_vertical(node->left, level + 1, "L");
    print_tree_vertical(node->right, level + 1, "R");
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
		check_exec(mini);
		//print_tree_vertical(mini->binary_tree, 0, "Root");
	//	exec_command(mini->binary_tree->cmd, mini);
		//execute_tree(mini->binary_tree, mini);
	}
}
