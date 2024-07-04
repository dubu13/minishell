/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 19:06:47 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/03 16:33:24 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**

	* Executes the appropriate built-in command based on the tokens in the mini shell.

	* This function iterates through the token list and calls the corresponding built-in
 * function for each recognized command, such as echo, pwd, cd, export, unset,
	and env.

	* The built-in functions are responsible for executing the command and updating the
 * mini shell state as necessary.
 *

	* @param mini The mini shell structure containing the token list and other state.
 */
void	exec_builtin(t_mini *mini)
{
	t_token	*current;

	current = mini->token_list;
	while (current)
	{
		if (!ft_strncmp(current->value, "echo", 4))
			ft_echo(current->next);
		else if (!ft_strncmp(current->value, "pwd", 3))
			ft_pwd();
		else if (!ft_strncmp(current->value, "cd", 2))
			ft_cd(current->next, mini);
		if (!ft_strncmp(current->value, "exit", 4))
			return (ft_exit(current->next));
		else if (!ft_strncmp(current->value, "export", 6))
			return (ft_export(current->next, mini));
		else if (!ft_strncmp(current->value, "unset", 5))
			return (ft_unset(current->next, mini));
		else if (!ft_strncmp(current->value, "env", 3))
			return (ft_env(current->next, mini));
		current = current->next;
	}
}

int	check_builtin(char *input)
{
	if (!ft_strncmp(input, "echo", 4))
		return (1);
	else if (!ft_strncmp(input, "pwd", 3))
		return (1);
	else if (!ft_strncmp(input, "cd", 2))
		return (1);
	else if (!ft_strncmp(input, "export", 6))
		return (1);
	else if (!ft_strncmp(input, "unset", 5))
		return (1);
	else if (!ft_strncmp(input, "env", 3))
		return (1);
	else if (!ft_strncmp(input, "exit", 4))
		return (1);
	return (0);
}

char	*command_path(char *command)
{
	int		i;
	int		len;
	char	*path;
	char	**directories;

	directories = ft_split(getenv("PATH"), ':');
	if (!directories)
		return (ft_putstr_fd \
		("minishell: Path environment variable not found\n", 2), NULL);
	i = -1;
	while (directories[++i])
	{
		len = ft_strlen(directories[i]);
		if (directories[i][len - 1] == '/')
			path = ft_strjoin(directories[i], command);
		else
		{
			path = ft_strjoin(directories[i], "/");
			path = ft_strjoin(path, command);
		}
		if (!(access(path, X_OK | F_OK)))
			return (path);
	}
	return (NULL);
}

char	**check_cmd(char **cmd)
{
	int		i;
	char	*arg;

	i = 0;
	while (cmd[i])
	{
		arg = remove_quotes(cmd[i]);
		free(cmd[i]);
		cmd[i] = arg;
		i++;
	}
	return (cmd);
}

void	external_command(char *input, t_mini *mini)
{
	char	*cmd_path;
	char	**cmd;
	pid_t	pid;
	int		status;

	cmd = split_cmd(input, ' ');
	cmd = check_cmd(cmd);
	if (!cmd)
		return ;
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	cmd_path = command_path(cmd[0]);
	if (!cmd_path)
		error(E_CMD, cmd[0]);
	if (pid == 0)
		execve(cmd_path, cmd, mini->env);
	else
		waitpid(pid, &status, 0);
	free(cmd_path);
	free(cmd);
}
