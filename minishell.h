/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:19:36 by dhasan            #+#    #+#             */
/*   Updated: 2024/05/26 18:35:25 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <linux/limits.h>
# include <stdlib.h>
# include <stdbool.h>

# define CYN "\001\033[36m\002" //	Cyan
# define RED "\001\033[31m\002" // Red

void	signal_handle(int sig);
int		ft_echo(char **args);
int     ft_pwd(void);
#endif