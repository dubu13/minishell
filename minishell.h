/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:19:36 by dhasan            #+#    #+#             */
/*   Updated: 2024/06/11 22:40:48 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "lib/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include <stdbool.h>

# define RESET "\033[0m"
# define CYN "\033[1;33m"  // Bold Yellow
# define YLW "\001\033[36m\002" //	Cyan
# define RED "\001\033[31m\002" // Red

typedef enum e_error_type
{
	E_SYNTAX,
	E_CMD,
	E_PERMISSION,
	E_EXPORT,
	E_ALLOC,
}	t_error_type;

typedef enum e_token_type
{
	WORD,
	PIPE,
	RDIR_IN,
	RDIR_OUT,
	RDIR_APPEND,
	RDIR_HEREDOC,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_mini
{
	char	**env;
	char	*input;
	t_token	*token_list;
}			t_mini;

//utils
int		is_str_closed(char *str);
//error
void	error(t_error_type type);
void	signal_handle(int sig);
//builtin
int		ft_echo(char **args);
int		ft_cd(char **path, t_mini *mini);
int		ft_pwd(void);
void	ft_env(char **env);
void	ft_export(char **args, t_mini *mini);
//builtin_utils
char	*put_quotes(char *env);
char	**sort_env(char **env);
char	**new_env(char **env, char *new);
//parse
char	*get_input(t_mini *mini);
// env_utils.c
int		index_env(char *type, char **env);
void	update_env(char *type, char *path, t_mini *mini);
char	*get_env(char **env, char *type);
char	**save_env(void);

void	tokenize(char *input, t_token **token_list);

#endif