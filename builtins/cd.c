/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/02 18:15:02 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Changes the current working directory to the specified path.
 *
 * @param new_path The new path to change the current working directory to.
 * @param old_path The previous current working directory path.
 * @param mini A pointer to the t_mini struct containing the shell environment.
 * @return 0 on success, EXIT_FAILURE on failure.
 */
int	cd_path(char *new_path, char *old_path, t_mini *mini)
{
	if (chdir(new_path) == -1)
		return (builtin_msg(E_CD, "no such file or directory"), EXIT_FAILURE);
	update_env("OLDPWD", old_path, mini);
	update_env("PWD", new_path, mini);
	return (0);
}

/**
 * Navigates up the directory hierarchy based on the provided path.
 *
 * @param old_path The current working directory path.
 * @param path The relative path to navigate up.
 * @return The new path after navigating up the directory hierarchy.
 */
char	*cd_up(char *old_path, char *path)
{
	char	*new_path;
	int		len;

	len = strlen(old_path) - 1;
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

int	ft_cd(t_token *input, t_mini *mini)
{
	char	*new_path;
	t_token	*temp;
	char	old_path[PATH_MAX];
	int		i;

	i = -1;
	temp = input;
	while (temp && temp->type == WORD)
	{
		i++;
		temp = temp->next;
	}
	if (i > 0)
		return (builtin_msg(E_CD, "too many arguments"), EXIT_FAILURE);
	if (!getcwd(old_path, PATH_MAX))
		return (builtin_msg(E_CD, "error getting current directory"), EXIT_FAILURE);
	new_path = get_newpath(input->value, old_path, mini);
	if (!new_path || cd_path(new_path, old_path, mini))
		return (builtin_msg(E_CD, "error getting path\n"), EXIT_FAILURE);
	return (0);
}
