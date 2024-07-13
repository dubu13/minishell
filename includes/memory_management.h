/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:13:21 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 03:14:31 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_MANAGEMENT_H
# define MEMORY_MANAGEMENT_H

# include "minishell.h"

/**
 * Frees the memory allocated for the minishell struct.
 *
 * @param mini The minishell struct to free.
 */
void    free_mini(t_mini *mini);

/**
 * Frees the memory allocated for the token list.
 *
 * @param token_list The token list to free.
 */
void    free_token_list(t_token **token_list);

/**
 * Frees the memory allocated for the binary tree.
 *
 * @param tree The binary tree to free.
 */
void    free_binary(t_tree *tree);

/**
 * Frees the memory allocated for the binary tree.
 *
 * @param tree The binary tree to free.
 */
void    free_tree(t_tree *tree);

/**
 * Frees the memory allocated for an array of strings.
 *
 * @param array The array of strings to free.
 */
void    free_array(char **array);

/**
 * Frees the memory allocated for a field and prints an error message.
 *
 * @param field The field to free.
 * @param type The type of error.
 * @param input The input that caused the error.
 */
void    free_and_error(char *field, t_error_type type, char *input);

#endif