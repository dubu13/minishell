/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:40:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/09 15:41:26 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
	// free(cwf);
	// free(cwd);

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
