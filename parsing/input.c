/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:40:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/09 17:44:06 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_prompt(t_mini *mini)
{
	char	cwd[PATH_MAX];
	char	*prompt;
	char	*cwf;
	char	*temp;

	(void)mini;
	getcwd(cwd, PATH_MAX);
	cwf = ft_strdup(ft_strrchr(cwd, '/') + 1);
	if (!cwf)
		cwf = ft_strdup(cwd);
	prompt = ft_strdup(CYN "minishell:" YLW);
	temp = ft_strjoin(prompt, cwf);
	free(prompt);
	prompt = ft_strjoin(temp, CYN "$ " RESET);
	free(cwf);
	free(temp);
	return (prompt);
}

char	*get_input(t_mini *mini)
{
	char	*input;
	char	*prompt;

	handle_signal();
	if (isatty(STDIN_FILENO))
	{
		rl_on_new_line();
		prompt = get_prompt(mini);
		input = readline(prompt);
		free(prompt);
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
