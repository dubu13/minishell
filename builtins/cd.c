/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/11 17:09:15 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	ft_cd(char **path, t_mini *mini)
{
	char	*new_path;
	char	old_path[PATH_MAX];

	if (!getcwd(old_path, PATH_MAX))
		return (perror("cd: error getting current directory"), EXIT_FAILURE);
	if (!*path || ((**path == '~' || **path == '.') \
		&& **path == '\0'))
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
