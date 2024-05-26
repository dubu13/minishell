#include "minishell.h"
//cd without the args and 'cd ~' -> HOME, change to user's home dir
//cd ~/, like this u can get relative path from home
//cd ~~ error
//when u get home w getenv check the path
int ft_cd(char **args)
{
    char    *new_path;
    char    old_path[PATH_MAX];

    // old_path = getcwd(old_path, PATH_MAX);

    if (!getcwd(old_path, PATH_MAX))
        return (printf("cd: error getting current dir"), EXIT_FAILURE);
    if (!*args || (*args[0] == '~' && *args[1] == '\0'))
    {
        new_path = getenv("HOME");
        if (!new_path)
            return (printf("cd: HOME not set\n"), EXIT_FAILURE);
    }
    if (chdir(*args))
        return(printf("cd: error home dir"));
    // else if (*args[0] == '~' && *args[1])
    if (access(new_path, X_OK | F_OK))
        return (printf("cd: no eccess to path"), EXIT_FAILURE);
    return (0);
}
