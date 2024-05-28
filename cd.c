/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/28 22:39:36 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cd without the args and 'cd ~' -> HOME, change to user's home dir
//cd ~/, like this u can get relative path from home
//cd ~~ error
//when u get home w getenv check the path

char	get_env(char **env, char *type)
{
	int	j;

	while (*env)
	{
		j = 0;
		while (*env[j] && (*env[j] == type[j]))
			j++;
		if (*env[j] == '=' && *env[j] != '\0' && *env[j] != ' ')
			return (ft_strdup(*env + j + 1));
	}
	return (ft_strdup(""));
}
//update function gonna be like:
//save in temp type and '=' -> "PWD="
//free old env(struct)
//join temp and path -> "PWD=/Users/dhasan/Desktop"
//then save it in env(struct)

int	cd_path(char *new_path, char *old_path)
{
	if (chdir(new_path) == -1) //or use access
		return (perror("cd : no such file or directory"), EXIT_FAILURE);
	//update oldpwd
	//update pwd
}

int	ft_cd(char **path, t_mini *mini)
{
	char	*new_path;
	char	old_path[PATH_MAX];

	if (!getcwd(old_path, PATH_MAX))
		return (perror("cd: error getting current directory"), EXIT_FAILURE);
	if (!*path || ((*path == '~' || *path == '.')
			&& (*path == '\0' || *path == '/')))
		new_path = get_env(mini, "HOME");
	else if (*path == '-' && !*(path + 1))
		new_path = get_env(mini, "OLDPWD");
	else
		new_path = ft_strdup(*path);
	if (!new_path)
		return (perror("cd: error getting path\n"), EXIT_FAILURE);
	if (!cd_path(new_path, old_path))
		return (EXIT_FAILURE);
	return (0);
}
	// if (chdir(new_path))
	// 	return (printf("cd: error home dir"));
	// if (access(new_path, X_OK | F_OK))
	// 	return (printf("cd: no eccess to path"), EXIT_FAILURE);
