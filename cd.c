/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/27 23:45:22 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cd without the args and 'cd ~' -> HOME, change to user's home dir
//cd ~/, like this u can get relative path from home
//cd ~~ error
//when u get home w getenv check the path
	// i = 0;
	// while (args[i])
	// {
	// 	j = 1;
	// 	while (args[i + j] && args[i + j] != '/')
	// 		j++;
	// 	temp = ft_calloc(j + 1, sizeof(char));
	// 	ft_strlcpy(temp, args + 1, j);
	// 	temp[j] = '\0';
	// }
char	*resolve_path(char *path)
{
	char	*temp;
	int		i;

	while (*path)
	{
		i = 1;
		while (*path + i && *path + i != '/')
			i++;
		temp = ft_calloc(i + 1, sizeof(char));
		ft_strlcpy(temp, path, i);
		if (!ft_strncmp(temp, "..", 2))
			
	}
}

char	*get_path(char *path)
{
	char	*new_path;
	char	*temp;
	int		i;
	int		j;
//for absolute path
	if (*path == '/')
		new_path = ft_strdup('/');
//for relative path
	else
		new_path = resolve_path(path);
}

int	ft_cd(char **path)
{
	char	*new_path;
	char	old_path[PATH_MAX];

	if (!getcwd(old_path, PATH_MAX))
	{
		perror("cd: error getting current directory");
		return (EXIT_FAILURE);
	}
	if (!*path || ((*path == '~' || *path == '.')
			&& (*path == '\0' || *path == '/')))
	{
		new_path = getenv("HOME");
		if (!new_path)
			return (printf("cd: HOME not set\n"), EXIT_FAILURE);
	}
	else if (*path[0] == '/')
		new_path = ft_strdup('/');
	else
		new_path = ft_strdup(old_path);
	return (0);
}
	// if (chdir(new_path))
	// 	return (printf("cd: error home dir"));
	// if (access(new_path, X_OK | F_OK))
	// 	return (printf("cd: no eccess to path"), EXIT_FAILURE);
