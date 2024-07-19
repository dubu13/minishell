/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:17:18 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/19 17:45:56 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

# include "minishell.h"

/**
 * @brief Handles a non-pipe node in the binary tree.
 *
 * @param current A pointer to the current node in the binary tree.
 * @param new_node The new node to be added to the binary tree.
 * @return A pointer to the updated binary tree.
 */
t_tree	*handle_non_pipe(t_tree **current, t_tree *new_node);

/**
 * @brief Handles a redirection node in the binary tree.
 *
 * @param node The node in the binary tree.
 * @param token The token associated with the redirection.
 */
void	handle_rdir(t_tree *node, t_token *token);

/**
 * @brief Handles a pipe node in the binary tree.
 *
 * @param root The root of the binary tree.
 * @param current A pointer to the current node in the binary tree.
 * @param pipe_node The pipe node to be added to the binary tree.
 * @return A pointer to the updated binary tree.
 */
t_tree	*handle_pipe(t_tree *root, t_tree **current, t_tree *pipe_node);

/**
 * @brief Initializes a new node in the binary tree with the given token.
 *
 * @param token The token to be used to initialize the new node.
 * @return A pointer to the new node.
 */
t_tree	*initialize_node(t_token *token);

/**
 * @brief Builds a binary tree from a list of tokens.
 *
 * @param tokens A pointer to the head of the token list.
 * @return A pointer to the root of the binary tree.
 */
t_tree	*build_tree(t_mini *mini, t_token **tokens);

/**
 * @brief Initializes a new node in the binary tree with the given token.
 *
 * @param token The token to be used to initialize the new node.
 * @return A pointer to the new node.
 */
t_tree	*initialize_node(t_token *token);

/**
 * @brief Creates an array of commands from the given token list.
 *
 * @param token The head of the token list.
 * @param cmd_count The number of commands in the token list.
 * @return An array of command strings.
 */
char	**create_cmd_array(t_token *token, int cmd_count, int i);

/**
 * @brief Creates an array of output redirection paths from the given token list.
 *
 * @param token The head of the token list.
 * @param out_count The number of output redirections in the token list.
 * @return An array of output redirection paths.
 */
char	**create_out_array(t_token *token, int out_count);

/**
 * @brief Creates an array of append redirection paths from
 *          the given token list.
 *
 * @param token The head of the token list.
 * @param append_count The number of append redirections in the token list.
 * @return An array of append redirection paths.
 */
char	**create_append_array(t_token *token, int append_count);

t_tree	*process_token(t_mini *mini, t_tree *root, \
			t_tree **current, t_token *token);

t_tree	*create_node(t_mini *mini, t_token *token);

char	**create_in_array(t_token *token, int in_count);

#endif
