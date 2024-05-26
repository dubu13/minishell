#include "minishell.h"

int ft_pwd(void)
{
    char    cwd[PATH_MAX];

    if (getcwd(cwd, PATH_MAX))
        printf("%s\n", cwd);
    else
        return(EXIT_FAILURE);
    return (0);
}