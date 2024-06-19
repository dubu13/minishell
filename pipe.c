/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkremer <dkremer@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:23:38 by dkremer           #+#    #+#             */
/*   Updated: 2024/06/19 14:42:15 by dkremer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// fd[0] - read 
// fd[1] - write
int fd[2];
if (pipe(fd) == -1)
{
    ft_printf("PIPE ERROR!\n");
    return error;
}
int id;
id = fork();
if (id == -1)
{
    ft_printf("FORK ERROR!\n");
    return error;
}
if (id == 0) // child process 
{
    close(fd[0]); // never read from pipe in child procces
    // do stuff with fd[1]
    if (write(fd[1], the_stuff, sizeof(stuff)) == -1)
    {
        printf("ERROR WRITING\n");
        return error;
    }
    close(fd[1]); // after writing close the write end of the pipe
}
else
{
    // parent process
    close(fd[1]); // never write to pipe in parent procces
    // do stuff with fd[0]
    if (read(fd[0], the_other_stuff, sizeof(stuff)) == -1)
    {
        printf("ERROR READING\n");
        return error;
    }
    close(fd[0]); //after reading close the read end of the pipe
}
return (0);

