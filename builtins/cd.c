/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/19 16:42:28 by dkremer          ###   ########.fr       */
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
		return (perror("cd : no such file or directory"), EXIT_FAILURE);
	if (access(new_path, X_OK | F_OK))
		return (perror("cd: no eccess to path"), EXIT_FAILURE);
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

	new_path = NULL;
	len = strlen(old_path) - 1;
	while (old_path[len] != '/' && len >= 0)
		len--;
	ft_strlcpy(new_path, old_path, len + 1);
	if (path[0] == '/')
		new_path = ft_strjoin(new_path, path);
	return (new_path);
}

int	ft_cd(t_token *input, t_mini *mini)
{
	char	*new_path;
	char	old_path[PATH_MAX];
	int		i;

	i = 0;
	while (input && input->type == WORD)
	{
		i++;
		input = input->next;
	}
	if (i > 0)
		return (perror("cd: too many arguments"), EXIT_FAILURE);
	if (!getcwd(old_path, PATH_MAX))
		return (perror("cd: error getting current directory"), EXIT_FAILURE);
	if (!input || ((input->value[0] == '~' || input->value[0] == '.')
			&& input->value[0] == '\0'))
		new_path = get_env(mini->env, "HOME");
	else if (**path == '-' && !*(*path + 1))
		new_path = get_env(mini->env, "OLDPWD");
	else if (**path == '.' && *(*path + 1) == '.')
		new_path = cd_up(old_path, *(path + 2));
	else
		new_path = ft_strdup(*path);
	if (!new_path || cd_path(new_path, old_path, mini))
		return (perror("cd: error getting path\n"), EXIT_FAILURE);
	return (0);
}
