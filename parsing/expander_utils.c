/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 02:14:17 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 02:14:44 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *handle_single_quote(char **temp, char *new_value)
{
    (*temp)++;
    while (**temp && **temp != '\'')
    {
        char *char_str = ft_substr(*temp, 0, 1);
        new_value = ft_strjoin_gnl(new_value, char_str);
        free(char_str);
        (*temp)++;
    }
    if (**temp == '\'')
        (*temp)++;
    return new_value;
}

char *handle_double_quote(char **temp, char *new_value, t_mini *mini)
{
    (*temp)++;
    while (**temp && **temp != '\"')
    {
        if (**temp == '$' && *(*temp + 1) != '\0')
            new_value = handle_env_expansion(temp, new_value, mini);
        else if (**temp == '\\' && (*(*temp + 1) == '\"' || *(*temp + 1) == '$'))
            new_value = handle_backslash(temp, new_value);
        else
            new_value = handle_regular_char(temp, new_value);
    }
    if (**temp == '\"')
        (*temp)++;
    return new_value;
}

char *handle_env_expansion(char **temp, char *new_value, t_mini *mini)
{
    (*temp)++;
    int key_len = 0;
    while ((*temp)[key_len] && (ft_isalnum((*temp)[key_len]) || (*temp)[key_len] == '_'))
        key_len++;
    char *env_key = ft_substr(*temp, 0, key_len);
    char *env_value = get_env(mini->env, env_key);
    if (env_value)
        new_value = ft_strjoin_gnl(new_value, env_value);
    free(env_key);
    *temp += key_len;
    return new_value;
}

char *handle_backslash(char **temp, char *new_value)
{
    (*temp)++;
    if (**temp)
    {
        char *char_str = ft_substr(*temp, 0, 1);
        new_value = ft_strjoin_gnl(new_value, char_str);
        free(char_str);
        (*temp)++;
    }
    return new_value;
}

char *handle_regular_char(char **temp, char *new_value)
{
    char *char_str = ft_substr(*temp, 0, 1);
    new_value = ft_strjoin_gnl(new_value, char_str);
    free(char_str);
    (*temp)++;
    return new_value;
}