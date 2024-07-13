/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:18:06 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 03:18:06 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

# include "minishell.h"

/**
 * @brief Handles input redirection in the binary tree.
 *
 * @param tree The root of the binary tree.
 * @param mini A pointer to the minishell struct.
 */
void	in_rdirect(t_tree *tree, t_mini *mini);

/**
 * @brief Handles output redirection in the binary tree.
 *
 * @param tree The root of the binary tree.
 * @param mini A pointer to the minishell struct.
 */
void	out_rdirect(t_tree *tree, t_mini *mini);

/**
 * @brief Handles append redirection in the binary tree.
 *
 * @param tree The root of the binary tree.
 * @param mini A pointer to the minishell struct.
 */
void	append_rdirect(t_tree *tree, t_mini *mini);

/**
 * @brief Handles heredoc redirection in the binary tree.
 *
 * @param tree The root of the binary tree.
 * @param mini A pointer to the minishell struct.
 */
void	heredoc(t_tree *tree, t_mini *mini);

#endif