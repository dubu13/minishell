/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:13:21 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/15 21:43:41 by dhasan           ###   ########.fr       */
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
void	free_mini(t_mini *mini);

/**
 * Frees the memory allocated for the token list.
 *
 * @param token_list The token list to free.
 */
void	free_token_list(t_token **token_list);

/**
 * Frees the memory allocated for the binary tree.
 *
 * @param tree The binary tree to free.
 */
void	free_binary(t_tree *tree);

/**
 * Frees the memory allocated for the binary tree.
 *
 * @param tree The binary tree to free.
 */
void	free_tree(t_tree *tree);

/**
 * Frees the memory allocated for an array of strings.
 *
 * @param array The array of strings to free.
 */
void	free_array(char **array);

#endif