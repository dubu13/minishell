/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 15:40:40 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 16:16:09 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
	// free(cwf);
	// free(cwd);

/**
 * Generates a prompt string for the minishell program.
 *
 * The prompt includes the current user's username, the current working directory,
 * and a shell prompt symbol. The prompt is formatted with ANSI escape codes to
 * provide color.
 *
 * @param mini A pointer to the t_mini struct containing the program's environment.
 * @return A dynamically allocated string containing the formatted prompt.
 */
char *get_prompt(t_mini *mini)
{
	char *prompt;
	char *cwf;
	char cwd[PATH_MAX];

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

/**
 * Reads user input from the terminal or standard input.
 *
 * If the program is running in an interactive terminal (isatty(STDIN_FILENO) is true),
 * this function uses readline() to read a line of input from the user, displays a prompt
 * using get_prompt(), and adds the input to the readline history.
 *
 * If the program is not running in an interactive terminal, this function uses
 * get_next_line() to read a line of input from standard input.
 *
 * @param mini A pointer to the t_mini struct containing the program's environment.
 * @return The user's input as a null-terminated string, or NULL if an error occurs or
 *         end-of-file is reached.
 */
char *get_input(t_mini *mini)
{
	char *input;

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
