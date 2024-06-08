/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:19:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/08 20:14:31 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	exec_builtin(char *cmd)
// {
// 	// if (!ft_strncmp(cmd, "echo", 4))
// 	// 	return (ft_echo());
// 	// if (!ft_strncmp(cmd, "pwd", 3))
// 	// 	return (ft_pwd());
// 	// if (!ft_strncmp(cmd, "cd", 2))
// 	// 	return (ft_cd());
// 	// if (!ft_strncmp(cmd, "exit", 4))
// 	// 	return ();
// 	// if (!ft_strncmp(cmd, "export", 6))
// 	// 	return ();
// 	// if (!ft_strncmp(cmd, "unset", 5))
// 	// 	return ();
// 	// if (!ft_strncmp(cmd, "env", 3))
// 	// 	return ();
// }

void	error(t_error_type type)
{
	if (type == E_SYNTAX)
		perror("Syntax error\n");
	if (type == E_CMD)
		perror("Command not found\n");
	if (type == E_PERMISSION)
		perror("Permission denied\n");
}

char	*get_prompt(t_mini *mini)
{
	char	*prompt;
	char	*cwf;
	char	cwd[PATH_MAX];

	getcwd(cwd, PATH_MAX);
	cwf = ft_strdup(ft_strrchr(cwd, '/') + 1);
	if (!cwf)
		cwf = ft_strdup(cwd);
	prompt = get_env(mini->env, "USER");
	prompt = ft_strjoin(CYN, prompt);
	prompt = ft_strjoin(prompt, "@minishell:" YLW);
	prompt = ft_strjoin(prompt, cwf);
	prompt = ft_strjoin(prompt, CYN "$ " RESET);
	// free(cwf);
	// free(cwd);
	return (prompt);
}

char	*get_input(t_mini *mini)
{
	char	*input;

	if (isatty(STDIN_FILENO))
	{
		rl_on_new_line();
		input = readline(get_prompt(mini));
	}
	else
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			return (NULL);
	}
	if (input && *input && isatty(STDIN_FILENO))
		add_history(input);
	return (input);
}

void	parse(t_mini *mini)
{
	mini->input = get_input(mini);
	if (!is_str_closed(mini->input))
		error(E_SYNTAX);
	tokenize();
}

t_mini	*init_mini(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (perror("Malloc"), NULL);
	mini->env = save_env();
	return (mini);
}

int	main(void)
{
	t_mini	*mini;

	mini = init_mini();
	parse(mini);
}
