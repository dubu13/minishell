/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:28:48 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 03:28:49 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPES_H
# define MINISHELL_TYPES_H

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
}               t_error_type;

typedef enum e_token_type
{
    WORD,
    PIPE,
    RDIR_IN,
    RDIR_OUT,
    RDIR_APPEND,
    RDIR_HEREDOC,
    CMD,
}               t_token_type;

typedef struct s_tree
{
    t_token_type    type;
    char            **cmd;
    char            *in;
    char            **out;
    char            **append;
    char            *limit;
    struct s_tree   *left;
    struct s_tree   *right;
}               t_tree;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
    struct s_token  *prev;
}               t_token;

typedef struct s_mini
{
    char            **env;
    char            *input;
    int             exit_status;
    char            **cmd_list;
    t_token         *token_list;
    t_tree          *binary_tree;
}               t_mini;

#endif