/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 14:39:07 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/16 14:40:24 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmd_path(char **directories, char *command)
{
	int		i;
	int		len;
	char	*path;
	char	*temp;

	i = -1;
	while (directories[++i])
	{
		len = ft_strlen(directories[i]);
		if (directories[i][len - 1] == '/')
			path = ft_strjoin(directories[i], command);
		else
		{
			temp = ft_strjoin(directories[i], "/");
			path = ft_strjoin(temp, command);
			free(temp);
		}
		if (!(access(path, X_OK | F_OK)))
			return (path);
		free(path);
	}
	return (NULL);
}

char	*command_path(char *command)
{
	char	**directories;
	char	*path;

	if (!ft_strncmp(command, "/", 1) || !ft_strncmp(command, "./", 2) \
		|| !ft_strncmp(command, "../", 3))
	{
		if (!access(command, X_OK | F_OK))
			return (ft_strdup(command));
		else
			return (NULL);
	}
	directories = ft_split(getenv("PATH"), ':');
	if (!directories)
		return (ft_putendl_fd \
		("minishell: Path environment variable not found", 2), NULL);
	path = get_cmd_path(directories, command);
	free_array(directories);
	return (path);
}
