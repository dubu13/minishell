/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:40:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/05 15:00:53 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (prompt);
}

char	*get_input(t_mini *mini)
{
	char	*input;

	handle_signal();
	if (isatty(STDIN_FILENO))
	{
		rl_on_new_line();
		input = readline(get_prompt(mini));
		if (!input)
			return (NULL);
	}
	else
	{
		input = get_next_line(STDIN_FILENO);
		if (!input)
			error(E_ALLOC, NULL);
	}
	if (input && *input && isatty(STDIN_FILENO))
		add_history(input);
	return (input);
}
