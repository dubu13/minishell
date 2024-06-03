/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:19:36 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/03 16:34:27 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>

# define CYN "\001\033[36m\002" //	Cyan
# define RED "\001\033[31m\002" // Red

typedef enum e_token_type
{
	WORD,
	PIPE,
	RDIR_IN,
	RDIR_OUT,
	RDIR_APPEND,
	RDIR_HEREDOC,
}	t_token_type;

typedef struct s_mini
{
	char	**env;
}			t_mini;

void	signal_handle(int sig);
int		ft_echo(char **args);
int		ft_cd(char **path, t_mini *mini);
int		ft_pwd(void);
char	*get_env(char **env, char *type);
int		index_env(char *type, char **env);
void	update_env(char *type, char *path, t_mini *mini);

#endif