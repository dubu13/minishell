/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 03:12:46 by dkremer           #+#    #+#             */
/*   Updated: 2024/07/13 03:34:22 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../lib/inc/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include "minishell_types.h"
# include "error_handling.h"
# include "memory_management.h"
# include "builtins.h"
# include "environment.h"
# include "input_processing.h"
# include "tokenization.h"
# include "binary_tree.h"
# include "execution.h"
# include "redirection.h"

# define RESET "\033[0m"
# define CYN "\033[1;33m"
# define YLW "\001\033[36m\002"
# define RED "\001\033[31m\002"

#endif