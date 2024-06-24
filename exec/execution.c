/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 13:14:50 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/24 21:17:29 by dhasan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
to execute external commands need to fork new process :

* The shell process should continue running independently of the command execution.
* The command should execute in its own process context, separate from the shell process.
* After executing the command, the shell needs to wait for its completion and possibly retrieve its exit status.
----------------
ex: Since ls is an external command located in /bin/ls,
you would fork a new process to execute /bin/ls and then wait for its completion.
*/

/*
to execute external commands:
1. fork a new process (fork())
2. execute the command in the child process (execve())
-> need to search for the command in the PATH environment variable
3. wait for the process to complete (waitpid() or wait())
*/