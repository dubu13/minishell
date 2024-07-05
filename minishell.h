/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:19:36 by dhasan            #+#    #+#             */
/*   Updated: 2024/07/05 12:55:54 by dkremer          ###   ########.fr       */
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
	char			**cmd_list;
	t_token			*token_list;
	t_tree			*binary_tree;
}					t_mini;

// utils
char				**split_cmd(char const *s, char c);
int					is_str_closed(char *str);
char				*remove_quotes(char *str);
long long			ft_atoull(const char *str, bool *error);
int					is_digit(const char *str);
// error
void				error(t_error_type type, char *input);
void				builtin_msg(t_error_type type, char *msg);
void				handle_signal(void);
void				handle_env_var(t_mini *mini);
// exec
int					check_builtin(char *input);
char				*command_path(char *command);
void				external_command(char *input, t_mini *mini);
void				exec_command(t_mini *mini);
void				expand_env(t_mini *mini, char *input, int i);
// builtin
int					ft_echo(t_token *input);
int					ft_cd(t_token *token, t_mini *mini);
void				ft_exit(t_token *input);
char				*get_newpath(char *input, char *old_path, t_mini *mini);
int					ft_pwd(void);
void				ft_env(t_token *input, t_mini *mini);
void				ft_export(t_token *input, t_mini *mini);
void				ft_unset(t_token *input, t_mini *mini);
void				exec_builtin(t_mini *mini);
// builtin_utils
char				*put_quotes(char *env);
char				**sort_env(char **env);
char				**new_env(char **env, char *new);
void				export_print(char **env);
// parse
char				*get_input(t_mini *mini);
// env_utils.c
int					index_env(char *type, char **env);
void				update_env(char *type, char *value, t_mini *mini);
char				*get_env(char **env, char *type);
char				**save_env(void);

void				tokenize(char *input, t_token **token_list);
t_token				*create_token(t_token_type type, char *value);
void				add_back_token(t_token **head, t_token *new_token);
int					skip_ws(char *input);
int					is_meta_char(char c);
int					is_append_heredoc(char *input);
int					count_pipes(t_token *token_list);
int					ft_pipe(t_mini *mini, t_token *token_list);
t_tree				*build_tree(t_token **tokens);
t_tree				*create_node(t_token *token);

void				handle_append_heredoc(char *input, int *i,
						t_token **token_list, int *is_next_cmd);
void				handle_meta_char(char *input, int *i, t_token **token_list,
						int *is_next_cmd);
void				handle_word(char *input, int *i, t_token **token_list,
						int *is_next_cmd);
void				process_word(char *input, int *i, t_token **token_list,
						int *is_next_cmd);
void				manage_token_creation(t_token **token_list, char *value,
						int *is_next_cmd);
void				token_type(char *input, int *i, t_token **token_list,
						int *is_next_cmd);
void				check_next_char(char *input, int *i, t_token **token_list,
						int *is_next_cmd);
void				execute_tree(t_tree *node, t_mini *mini);
t_tree				*initialize_node(t_token *token);
char				**create_cmd_array(t_token *token, int cmd_count);
t_tree				*process_token(t_tree *root, t_tree **current,
						t_token *token);
t_token_type		set_type(int *is_next_cmd);

void	free_token_list(t_token *token_list);
void free_tree(t_tree *tree);
void free_mini(t_mini *mini);

#endif
