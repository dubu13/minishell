/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/07 05:32:33 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_path(char *new_path, char *old_path, t_mini *mini)
{
	if (chdir(new_path) == -1)
		return (builtin_msg(E_CD, "no such file or directory"), EXIT_FAILURE);
	update_env("OLDPWD", old_path, mini);
	update_env("PWD", new_path, mini);
	return (0);
}

char	*cd_up(char *old_path, char *path)
{
	char	*new_path;
	int		len;

	len = ft_strlen(old_path) - 1;
	while (old_path[len] != '/' && len >= 0)
		len--;
	new_path = ft_calloc(len + 1, sizeof(char));
	if (!new_path)
		error(E_ALLOC, NULL);
	ft_strlcpy(new_path, old_path, len + 1);
	new_path[len + 1] = '\0';
	while (*path && *path == '.')
		path++;
	if (*path == '/')
		new_path = ft_strjoin(new_path, path);
	return (new_path);
}

char	*get_newpath(char *input, char *old_path, t_mini *mini)
{
	char	*new_path;

	if (!input || (*input == '~' && *(input + 1) == '\0'))
		new_path = get_env(mini->env, "HOME");
	else if (*input == '.' && *(input + 1) == '\0')
		new_path = ft_strdup(old_path);
	else if (*input == '-' && *(input + 1) == '\0')
		new_path = get_env(mini->env, "OLDPWD");
	else if (*input == '.' && *(input + 1) == '.')
		new_path = cd_up(old_path, input);
	else
		new_path = ft_strdup(input);
	return (new_path);
}

void	ft_cd(char **input, t_mini *mini)
{
	int		i;
	char	*new_path;
	char	old_path[PATH_MAX];

	i = 0;
	while (input[i])
		i++;
	if (i > 1)
	{
		builtin_msg(E_CD, "too many arguments");
		mini->exit_status = 2;
		return ;
	}
	if (!getcwd(old_path, PATH_MAX))
	{
		builtin_msg(E_CD, "error getcwd");
		mini->exit_status = 1;
	}
	new_path = get_newpath(input[0], old_path, mini);
	if (!new_path || cd_path(new_path, old_path, mini))
	{
		builtin_msg(E_CD, "error getting path\n");
		mini->exit_status = 1;
	}
	free(new_path);
}
