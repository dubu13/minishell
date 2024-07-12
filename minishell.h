/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:19:36 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/12 22:28:07 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "lib/inc/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define RESET "\033[0m"
# define CYN "\033[1;33m"       // Bold Yellow
# define YLW "\001\033[36m\002" //	Cyan
# define RED "\001\033[31m\002" // Red

typedef enum e_error_type
{
	E_SYNTAX,
	E_CMD,
	E_PERMISSION,
	E_EXPORT,
	E_ALLOC,
	E_UNSET,
	E_EXIT,
	E_CD,
}					t_error_type;

typedef enum e_token_type
{
	WORD,
	PIPE,
	RDIR_IN,
	RDIR_OUT,
	RDIR_APPEND,
	RDIR_HEREDOC,
	CMD,
}					t_token_type;

typedef struct s_tree
{
	t_token_type	type;
	char			**cmd;
	char			*in;
	char			**out;
	char			**append;
	char			*limit;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_mini
{
	char			**env;
	char			*input;
	int				exit_status;
	char			**cmd_list;
	t_token			*token_list;
	t_tree			*binary_tree;
}					t_mini;

// utils
int					is_str_closed(char *str);
char				*remove_quotes(char *str);
// error
void				error(t_error_type type, char *input);
void				builtin_msg(t_error_type type, char *msg);
void				handle_signal(void);
// free
void				free_mini(t_mini *mini);
void				free_token_list(t_token **token_list);
void				free_binary(t_tree *tree);
void				free_tree(t_tree *tree);
void				free_array(char **array);
void				free_and_error(char *field, t_error_type type, char *input);
// builtin
void				ft_echo(char **input, t_mini *mini);
void				ft_cd(char **token, t_mini *mini);
void				ft_exit(char **input, t_mini *mini);
void				ft_pwd(char **cmd, t_mini *mini);
void				ft_env(char **input, t_mini *mini);
void				ft_export(char **input, t_mini *mini);
void				ft_unset(char **input, t_mini *mini);
// builtin_utils
char				*put_quotes(char *env);
char				**sort_env(char **env);
char				**new_env(char **env, char *new);
// parse
char				*get_input(t_mini *mini);
void				parse(t_mini *mini);
// env_utils.c
int					index_env(char *type, char **env);
void				update_env(char *type, char *value, t_mini *mini);
char				*get_env(char **env, char *type);
char				**save_env(void);
// token
void				tokenize(char *input, t_token **token_list);
t_token				*create_token(t_token_type type, char *value);
void				add_back_token(t_token **head, t_token *new_token);
// token utils
int					skip_ws(char *input);
int					is_meta_char(char c);
int					is_append_heredoc(char *input);
int					is_not_space(char *input, int i);
void				handle_quotes_with_space(char *input, int *i);
void				count_tokens(t_token *token, int *counts);
t_token_type		set_type(int *is_next_cmd);
// binary_tree
t_tree				*build_tree(t_token **tokens);
t_tree				*initialize_node(t_token *token);
char				**create_cmd_array(t_token *token, int cmd_count);
char				**create_out_array(t_token *token, int out_count);
char				**create_append_array(t_token *token, int append_count);
//binary_tree utils
t_tree				*handle_non_pipe(t_tree **current, t_tree *new_node);
t_tree				*handle_pipe(t_tree *root, t_tree **current, \
						t_tree *pipe_node);
void				handle_rdir(t_tree *node, t_token *token);
//execution
void				exec_node(t_tree *node, t_mini *mini);
int					check_builtin(char *input);
void				external_command(char **cmd, t_mini *mini);
void				exec_builtin(char **cmd, t_mini *mini);
//pipe and redirects
void				exec_pipe(t_tree *tree, t_mini *mini);
void				in_rdirect(t_tree *tree, t_mini *mini);
void				out_rdirect(t_tree *tree, t_mini *mini);
void				append_rdirect(t_tree *tree, t_mini *mini);
void				heredoc(t_tree *tree, t_mini *mini);

#endif
