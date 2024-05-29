/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:40:12 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/29 19:17:14 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
//cd without the args and 'cd ~' -> HOME, change to user's home dir
//cd ~/, like this u can get relative path from home
//cd ~~ error
//when u get home w getenv check the path

//update function gonna be like:
//save in temp type and '=' -> "PWD="
//free old env(struct)
//join temp and path -> "PWD=/Users/dhasan/Desktop"
//then save it in env(struct)

void	update_env(char *type, char *path, t_mini *mini)
{
	char	*temp;
	int		i;

	i = index_env(type, mini->env);
	if (i == -1)
		exit (EXIT_FAILURE);
	free(mini->env[i]);
	temp = ft_strjoin(type, '=');
	mini->env[i] = ft_strjoin(temp, path);
	free(temp);
}
int	cd_up()
{
	//go upper dir
	//let's say pwd is ->/users/dhasan/desktop/projects/minishell
	//delete minishell ->/users/dhasan/desktop/projects

	//check if there '/' after '..'
	//if there is go that dir
	//just add the path after '..' ->/users/dhasan/desktop/projects + /philo
	
}

int	cd_path(char *new_path, char *old_path, t_mini *mini)
{
	if (chdir(new_path) == -1) //or use access
		return (perror("cd : no such file or directory"), EXIT_FAILURE);
	update_env("OLDPWD", old_path, mini);
	update_env("PWD", new_path, mini);
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
	else if (*path == '.' && *path + 1 == '.')
		new_path = cd_up();
	else
		new_path = ft_strdup(*path);
	if (!new_path || !cd_path(new_path, old_path, mini))
		return (perror("cd: error getting path\n"), EXIT_FAILURE);
	return (0);
}
	// if (chdir(new_path))
	// 	return (printf("cd: error home dir"));
	// if (access(new_path, X_OK | F_OK))
	// 	return (printf("cd: no eccess to path"), EXIT_FAILURE);
