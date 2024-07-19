/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/19 19:22:54 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_path(char *new_path, char *old_path, t_mini *mini)
{
	if (chdir(new_path) == -1)
	{
		if (access(new_path, F_OK) == -1)
			return (builtin_msg(E_CD, "no such file or directory"), EXIT_FAILURE);
		else
			return (builtin_msg(E_CD, "not a directory"), EXIT_FAILURE);
	}
	update_env("OLDPWD", old_path, mini);
	update_env("PWD", new_path, mini);
	return (0);
}

char	*get_newpath(char *input, t_mini *mini)
{
	char	*new_path;

	if (!input || (*input == '~' && *(input + 1) == '\0'))
		new_path = get_env(mini->env, "HOME");
	else if (*input == '-' && *(input + 1) == '\0')
	{
		new_path = get_env(mini->env, "OLDPWD");
		printf("%s\n", new_path);
	}
	else
		new_path = input;
	if (!new_path)
		builtin_msg(E_CD, "path not set");
	return (new_path);
}

void	ft_cd(char **input, t_mini *mini)
{
	int		i;
	char	*new_path;
	char	old_path[PATH_MAX];

	i = 0;
	mini->exit_status = 0;
	while (input[i])
		i++;
	if (i > 1)
		return (builtin_msg(E_CD, "too many arguments"),
			mini->exit_status = 2, (void)0);
	if (!getcwd(old_path, PATH_MAX))
		return (builtin_msg(E_CD, "error getcwd"),
			mini->exit_status = 1, (void)0);
	new_path = get_newpath(input[0], mini);
	if (!new_path || cd_path(new_path, old_path, mini))
		mini->exit_status = 1;
}
