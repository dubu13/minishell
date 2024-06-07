#ifndef NOTES_H
# define NOTES_H

# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>

/**
	@note//_DESCRIPTION
	@brief #### Check file access permissions.
	@brief Checks whether the calling process can access the file in the path
		`pathname` with the permissions specified by `mode`.
	@note//_PARAMETERS
	@param pathname The path to the file to be checked.
	@param mode The permissions to be checked. The permissions can be combined
		using the bitwise OR operator.
	@note//_RETURNS
	@return 0 if the file can be accessed with the permissions specified by
		`mode`, or -1 if an error occurred.
	@note//_NOTES
	@note available permissions are: R_OK, W_OK, X_OK, F_OK. Read, Write, Execute
		and File exists respectively.
 */
int				access(const char *pathname, int mode);

/**
	@note//_DESCRIPTION
	@brief #### Read a line from the standard input.
	@brief The function reads a line from the standard input using `prompt` as
		the prompt.
	@note//_PARAMETERS
	@param prompt The prompt to be displayed to the user.
	@note//_RETURNS
	@return A pointer to the line read from the standard input, or NULL nothing
		was read.
	@note//_WARNINGS
	@warning The function returns a pointer that must be freed by the caller.
 */
char			*readline(const char *prompt);

/**
	@note//_DESCRIPTION
	@brief #### Deletes the history.
	@brief Clears the history list by deleting all the entries.
 */
void			rl_clear_history(void);

/**
	@note//_DESCRIPTION
	@brief #### Tells the library that the cursor has moved to a new line.
	@brief The function updates the internal state of the library to reflect the
		fact that the cursor has moved to a new line.
	@note//_RETURNS
	@return
	@note//_NOTES
	@note No info on the return value.
 */
int				rl_on_new_line(void);

/**
	@note//_DESCRIPTION
	@brief #### Replaces the contents of the line with `text`.
	@brief Replace the contents of the line with `text`. If `clear_undo` is
		non-zero, the undo list is cleared.
	@note//_PARAMETERS
	@param text the text to replace the contents of the line with.
	@param clear_undo if non-zero, the undo list is cleared.
 */
void			rl_replace_line(const char *text, int clear_undo);

/**
	@note//_DESCRIPTION
	@brief #### Refreshes the display.
	@brief The function refreshes the display, updating the screen to reflect
		the current state of the line.
 */
void			rl_redisplay(void);

/**
	@note//_DESCRIPTION
	@brief #### Adds a line to the history.
	@brief Adds `line` to the history list.
	@note//_PARAMETERS
	@param line The line to be added to the history list.
	@note//_NOTES
	@note The line still needs to be freed by the caller.
 */
void			add_history(const char *line);

/**
	@note//_DESCRIPTION
	@brief #### Wait for a child process to terminate.
	@brief The function suspends the execution of the calling process until one
		of its child processes terminates.
	@note//_PARAMETERS
	@param status A pointer to the location where the status of the terminated
		child process is to be stored.
	@note//_RETURNS
	@return The process ID of the terminated child process, or -1 if an error
		occurred.
 */
pid_t			wait(int *status);

/**
	@note//_DESCRIPTION
	@brief #### Same as wait4, but with `pid` set to -1.
	@brief Waits for any child process to terminate.
 */
pid_t			wait3(int *status, int options, struct rusage *rusage);

/**
	@note//_DESCRIPTION
	@brief #### Wait for a child process to terminate.
	@brief Waits for a child process to terminate, and returns the process ID of
		the terminated child process.
	@note//_PARAMETERS
	@param pid specifies the process ID of the child process to wait for.
	@param status a pointer to the location where the status of the terminated
		child process is to be stored.
	@param options The options to be used. The options can be combined using the
		bitwise OR operator.
	@param rusage if not NULL, a pointer to a `rusage` structure where the
		resource usage of the terminated child process is to be stored.
	@note//_RETURNS
	@return The process ID of the terminated child process, or -1 if an error
		occurred, or 0 if `WNOHANG` was specified and no child process wants to
		report.
	@note//_NOTES
	@note if `pid` is -1, the function waits for any child process.
	@note if `pid` is 0, the function waits for any child process in the same
		process group as the calling process.
	@note if `pid` is smaller than -1, the function waits for any child process
		whose process group ID is equal to the absolute value of `pid`.
	@note The `options` parameter can be 0 or a combination of the following
		flags:
	@note - `WNOHANG`: return immediately if no child has exited.
	@note - `WUNTRACED`: also return if a child has stopped.
	@note Availible macros for `status` (One of the first three is always true):
	@note - `WIFEXITED`: returns true if the child terminated normally.
	@note - `WIFSIGNALED`: returns true if the child process was
		terminated by a signal.
	@note - `WIFSTOPPED`: returns true if the child process was stopped by a
		signal and can be restarted. (This macro is only available if the
		`WUNTRACED` option was specified or if the child process is being traced.)
	@note - `WEXITSTATUS`: returns the exit status of the child.
	@note - `WTERMSIG`: if `WIFSIGNALED` is true, returns the signal number that
		terminated the child process.
	@note - `WCOREDUMP`: if `WIFSIGNALED` is true, returns true if the child
		produced a core file with an image of the process when it terminated.
	@note - `WSTOPSIG`: if `WIFSTOPPED` is true, returns the signal number that
		stopped the child process.
	@note if the parent process finishes before the child process, the remaining
		child process are assigned the parent process 1 ID.
 */
pid_t			wait4(pid_t pid, int *status, int options,
					struct rusage *rusage);

/**
	@note//_DESCRIPTION
	@brief #### Same as wait4, but with `rusage` set to NULL.
	@brief Waits for a child process to terminate, and returns the process ID of
		the terminated child process.
 */
pid_t			waitpid(pid_t pid, int *status, int options);

/**
	@note//_DESCRIPTION
	@brief #### Catch a signal.
	@brief The function catches the signal `sig` and calls the function
		`handler` when the signal is received to handle the signal.
	@note//_PARAMETERS
	@param sig The signal to be caught.
	@param handler The function to be called when the signal is received.
	@note//_NOTES
	@note To see the list of available signals, see the `<signal.h>` header file
 */
void			signal(int sig, void *handler(int sig));

/**
	@note//_DESCRIPTION
	@brief #### Set the action for a signal.
	@brief The function sets the action for the signal `sig` to the action
		specified by `act`. If `oact` is not NULL, the previous action is stored
		in the location pointed to by `oact`.
	@note//_PARAMETERS
	@param sig The signal to be set.
	@param act The structure containing the new action for the signal.
	@param oact A pointer to the location where the previous action for the
		signal is to be stored.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
	@note//_NOTES
	@note There is a lot, for more info see the man page
 */
int				sigaction(int sig, const struct sigaction *act,
					struct sigaction *oact);

/**
	@note//_DESCRIPTION
	@brief #### Initialize a empty signal set.
	@brief The function initializes the signal set `set` to an empty set.
	@note//_PARAMETERS
	@param set The signal set to be initialized.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
	@note//_NOTES
	@note It should be used in every signal set to initialize it.
 */
int				sigemptyset(sigset_t *set);

/**
	@note//_DESCRIPTION
	@brief #### Function adds a signal to a set.
	@brief The function adds the signal `signum` to the signal set `set`.
	@note//_PARAMETERS
	@param set The signal set to which the signal is to be added.
	@param signum The signal to be added to the signal set.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
 */
int				sigaddset(sigset_t *set, int signum);

/**
	@note//_DESCRIPTION
	@brief #### Sends a signal to a process.
	@brief The function sends the signal `sig` to the process with the process ID
		`pid`.
	@note//_PARAMETERS
	@param pid The process ID of the process to which the signal is to be sent.
	@param sig The signal to be sent.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
	@note//_NOTES
	@note if `pid` is 0, the signal is sent to all processes in the process group
		of the calling process.
	@note if `pid` is -1, if sudo, the signal will be sent to all processe,
		otherwise the signal is sent to all processes with the same uid as the
		calling process, either way the calling process is excluded. No error
		is returned if any process was signaled.
 */
int				kill(pid_t pid, int sig);

/**
	@note//_DESCRIPTION
	@brief #### Gets the path of the current working directory.
	@brief The function gets the path of the current working directory and stores
		it in the buffer pointed to by `buf`.
	@note//_PARAMETERS
	@param buf A pointer to the buffer where the path of the current working
		directory is to be stored.
	@note//_RETURNS
	@return the pointer to the buffer where the path of the current working
		directory is stored, or NULL if an error occurred.
	@note//_NOTES
	@note if `buf` is NULL, the function allocates a buffer of size `size` and
		stores the path of the current working directory in the buffer.
	@note//_WARNINGS
	@warning The buffer returned by the function must be freed by the caller.
 */
char			*getcwd(char *buf);

/**
	@note//_DESCRIPTION
	@brief #### Changes the current working directory.
	@brief The function changes the current working directory to the directory
		specified by `path`.
	@note//_PARAMETERS
	@param path The path of the directory to which the current working directory
		is to be changed.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
 */
int				chdir(const char *path);

/**
	@note//_DESCRIPTION
	@brief #### Obtains information about a file.
	@brief The function obtains information about the file specified by `pathname`
		and stores it in the structure pointed to by `statbuf`.
	@note//_PARAMETERS
	@param pathname The path of the file about which information is to be
		obtained.
	@param statbuf A pointer to the structure where the information about the
		file is to be stored.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
 */
int				stat(const char *pathname, struct stat *statbuf);

/**
	@note//_DESCRIPTION
	@brief #### Obtains information about a link.
	@brief The function obtains information about the link specified by `pathname`
		and stores it in the structure pointed to by `statbuf`.
	@note//_PARAMETERS
	@param pathname The path of the link about which information is to be
		obtained.
	@param statbuf A pointer to the structure where the information about the
		link is to be stored.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
 */
int				lstat(const char *pathname, struct stat *statbuf);

/**
	@note//_DESCRIPTION
	@brief #### Obtains information about an open file.
	@brief The function obtains information about the open file specified by `fd`
		and stores it in the structure pointed to by `statbuf`.
	@note//_PARAMETERS
	@param fd The file descriptor of the open file about which information is to
		be obtained.
	@param statbuf A pointer to the structure where the information about the
		open file is to be stored.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
 */
int				fstat(int fd, struct stat *statbuf);

/**
	@note//_DESCRIPTION
	@brief #### Removes the link to a file.
	@brief The function removes the link to the file specified by `pathname` and
		decreases the link count of the file by 1. If the link count of the file
		becomes 0, the file is deleted.
	@note//_PARAMETERS
	@param pathname The path of the file to be unlinked.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
	@note//_NOTES
	@note If the file link count is 0 but the file is still open, the file is
		not deleted until it is closed.
 */
int				unlink(const char *pathname);

/**
	@note//_DESCRIPTION
	@brief #### Starts a new process.
	@brief The function replaces the current process with a new process image
		specified by `pathname`. The new process image is obtained by loading a
		file into memory and starting its execution.
	@note//_PARAMETERS
	@param pathname The path of the file containing the new process image.
	@param argv An array of pointers to null-terminated strings that represent
		the argument list available to the new process.
	@param envp An array of pointers to null-terminated strings that represent
		the environment list available to the new process.
	@note//_RETURNS
	@return -1 if an error occurred, or the function does not return if it
		succeeds.
	@note//_NOTES
	@note Use in combination with `fork` to create a new process, so the parent
		process can continue to execute.
 */
int				execve(const char *pathname, char *const argv[],
					char *const envp[]);

/**
	@note//_DESCRIPTION
	@brief #### Duplicates a file descriptor.
	@brief The function duplicates the file descriptor `fd` and returns a new file
		descriptor that refers to the same open file description.
	@note//_PARAMETERS
	@param fd The file descriptor to be duplicated.
	@note//_RETURNS
	@return The new file descriptor, or -1 if an error occurred.
 */
int				dup(int fd);

/**
	@note//_DESCRIPTION
	@brief #### Duplicates a file descriptor.
	@brief Duplicates the file descriptor `oldfd` to the file descriptor
		`newfd`.
	@note//_PARAMETERS
	@param oldfd The file descriptor to be duplicated.
	@param newfd The file descriptor to which the file descriptor `oldfd` is to
		be duplicated.
	@note//_RETURNS
	@return `newfd` if the function succeeds, or -1 if an error occurred.
	@note//_NOTES
	@note If `newfd` is already open, it is closed first.
	@note//_WARNINGS
	@warning Both file descriptors must be closed by the caller.
 */
int				dup2(int oldfd, int newfd);

/**
	@note//_DESCRIPTION
	@brief #### Creates a pipe.
	@brief The function creates a pipe, a unidirectional data channel that can be
		used for interprocess communication.
	@note//_PARAMETERS
	@param pipefd An array of two integers where the file descriptors for the
		read and write ends of the pipe are to be stored.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
	@note//_NOTES
	@note `pipefd[0]` refers to the read end of the pipe, and `pipefd[1]` refers
		to the write end of the pipe.
	@note//_WARNINGS
	@warning Both file descriptors must be closed by the caller.
	@warning If the pipe is used by a forked process, the file descriptors must
		be closed in both the parent and child processes.
 */
int				pipe(int pipefd[2]);

/**
	@note//_DESCRIPTION
	@brief #### Opens a directory stream.
	@brief The function opens the directory specified by `name` and returns a
		pointer to the directory stream.
	@note//_PARAMETERS
	@param name The path of the directory to be opened.
	@note//_RETURNS
	@return A pointer to the directory stream, or NULL if an error occurred.
	@note//_NOTES
	@note The directory stream can be read using the `readdir` function.
	@note//_WARNINGS
	@warning The directory stream must be closed by the caller with the
		`closedir` function.
 */
DIR				*opendir(const char *name);

/**
	@note//_DESCRIPTION
	@brief #### Reads a directory entry.
	@brief The function reads the next directory entry from the directory stream
		`dirp`.
	@note//_PARAMETERS
	@param dirp The directory stream to be read.
	@note//_RETURNS
	@return A pointer to the next directory entry, or NULL if the end of the
		directory stream is reached or an error occurred.
	@note//_NOTES
	@note The order in which the directory entries are read is unspecified.
 */
struct dirent	*readdir(DIR *dirp);

/**
	@note//_DESCRIPTION
	@brief #### Closes a directory stream.
	@brief The function closes the directory stream `dirp`.
	@note//_PARAMETERS
	@param dirp The directory stream to be closed.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
 */
int				closedir(DIR *dirp);

/**
	@note//_DESCRIPTION
	@brief #### Search for the message string corresponding to an error number.
	@brief The function returns a pointer to the message string corresponding to
		the error number `errnum`.
	@note//_PARAMETERS
	@param errnum The error number for which the message string is to be
		returned.
	@note//_RETURNS
	@return A pointer to the message string corresponding to the error number, or
		EINVAL if the error number is not recognized.
	@note//_NOTES
	@note
	@note//_WARNINGS
	@warning
 */
char			*strerror(int errnum);

/**
	@note//_DESCRIPTION
	@brief #### Prints a message to the standard error.
	@brief The function prints the message `s` prepended to the message string
		corresponding to the value of `errno` to the standard error.
	@note//_PARAMETERS
	@param s The message to be printed to the standard error.
	@note//_NOTES
	@note If `s` is NULL, the function prints the message corresponding to the
		value of `errno`.
 */
void			perror(const char *s);

/**
	@note//_DESCRIPTION
	@brief #### Determines if a file descriptor refers to a terminal.
	@brief The function determines if the file descriptor `fd` refers to a
		terminal type device.
	@note//_PARAMETERS
	@param fd The file descriptor to be checked.
	@note//_RETURNS
	@return 1 if the file descriptor refers to a terminal type device, or 0 if
		it does not.
 */
int				isatty(int fd);

/**
	@note//_DESCRIPTION
	@brief #### Gets the name of the terminal.
	@brief The function returns the name of the terminal associated with the file
		descriptor `fd`.
	@note//_PARAMETERS
	@param fd The file descriptor of the terminal.
	@note//_RETURNS
	@return A pointer to the name of the terminal, or NULL if an error occurred.
	@note//_NOTES
	@note The name of the terminal is stored in a static buffer that is
		overwritten by each call to the function.
 */
char			*ttyname(int fd);

/**
	@note//_DESCRIPTION
	@brief #### Gets the file descriptor of the terminal.
	@brief The function returns the file descriptor of the terminal associated
		with the current process.
	@note//_RETURNS
	@return The file descriptor of the terminal, or -1 if an error occurred.
	@note//_NOTES
	@note ttyslot is a legacy function that is not recommended for use in new
		programs.
 */
int				ttyslot(void);

/**
	@note//_DESCRIPTION
	@brief #### Input/output control.
	@brief The function performs the operation specified by `request` on the
		file descriptor `fd`.
	@note//_PARAMETERS
	@param fd The file descriptor on which the operation is to be performed.
	@param request The operation to be performed.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
	@note//_NOTES
	@note Macros and definitions for `request` can be found in the
		`<sys/ioctl.h>` header file.
	@note Is not reliable, use other system calls if possible.
	@note//_WARNINGS
	@warning The function is not recommended for use in new programs, should be
		used just when other system calls are not available.
 */
int				ioctl(int fd, unsigned long request, ...);

/**
	@note//_DESCRIPTION
	@brief #### Gets the value of an environment variable.
	@brief The function returns the value of the environment variable `name`.
	@note//_PARAMETERS
	@param name The name of the environment variable.
	@note//_RETURNS
	@return A pointer to the value of the environment variable, or NULL if the
		environment variable does not exist.
	@note//_NOTES
	@note The process should not modify the value of the environment variable.
 */
char			*getenv(const char *name);

/**
	@note//_DESCRIPTION
	@brief #### Copies the parameters from the file descriptor.
	@brief The function copies the parameters from the file descriptor `fd` and
		stores them in the structure pointed to by `termios_p`.
	@note//_PARAMETERS
	@param fd The file descriptor from which the parameters are to be copied.
	@param termios_p A pointer to the structure where the parameters are to be
		stored.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
 */
int				tcgetattr(int fd, struct termios *termios_p);

/**
	@note//_DESCRIPTION
	@brief #### Sets the parameters of the file descriptor.
	@brief The function sets the parameters of the file descriptor `fd` to the
		parameters specified by `termios_p`.
	@note//_PARAMETERS
	@param fd The file descriptor whose parameters are to be set.
	@param optional_actions Optional actions to be taken.
	@param termios_p A pointer to the structure containing the parameters to be
		set.
	@note//_RETURNS
	@return 0 if the function succeeds, or -1 if an error occurred.
	@note//_NOTES
	@note You can use multiple options in `optional_actions` by using the bitwise
		OR operator.
	@note The `optional_actions` parameter can be one of the following values:
	@note - `TCSANOW`: the change occurs immediately.
	@note - `TCSADRAIN`: the change occurs after all output written to the file
		descriptor has been transmitted.
	@note - `TCSAFLUSH`: the change occurs after all output written to the file
		descriptor has been transmitted, and all input that has been received but
		not read is discarded.
	@note - `TCSASOFT`: the values of the `c_cflag`, `c_ispeed`, and `c_ospeed`
		members of the `termios` structure are not changed.
	@note//_WARNINGS
	@warning
 */
int				tcsetattr(int fd, int optional_actions,
					const struct termios *termios_p);

/**
	@note//_DESCRIPTION
	@brief #### Gets the Terminfo entry.
	@brief Gets the Terminfo entry for the terminal type specified by `name` and
		stores it in the buffer pointed to by `bp`.
	@note//_PARAMETERS
	@param bp A pointer to the buffer where the Terminfo entry is to be stored.
	@param name The name of the terminal type.
	@note//_RETURNS
	@return 1 if the Terminfo entry was found, 0 if the Terminfo entry was not
		found, or -1 if the terminfo database could not be found.
 */
int				tgetent(char *bp, const char *name);

/**
	@note//_DESCRIPTION
	@brief #### Gets the flag capacity.
	@brief Gets the boolean capacity specified by `id` from the Terminfo entry
		and returns its value.
	@note//_PARAMETERS
	@param id The name of the capacity to look for.
	@note//_RETURNS
	@return 1 if the flag is true, 0 if the flag is not avalaible.
 */
int				tgetflag(const char *id);

/**
	@note//_DESCRIPTION
	@brief #### Gets the numbe capacitiy.
	@brief Gets the number capacity specified by `id` from the Terminfo entry
		and returns its value.
	@note//_PARAMETERS
	@param id The name of the capacity to look for.
	@note//_RETURNS
	@return The value of the number entry, or -1 if the number entry is not
		avaliable.
 */
int				tgetnum(const char *id);

/**
	@note//_DESCRIPTION
	@brief #### Gets the string.
	@brief Gets the string entry specified by `id` from the Terminfo entry and
		returns its value.
	@note//_PARAMETERS
	@param id The name of the Terminfo entry to retrieve the value from.
	@param area A pointer to the area where the string is to be stored.
	@note//_RETURNS
	@return A pointer to the string entry, or NULL if the string entry is not
		avaliable.
	@note//_NOTES
	@note The `area` parameter will be updated to point after the NULL character
		of the string.
 */
char			*tgetstr(const char *id, char **area);

/**
	@note//_DESCRIPTION
	@brief #### Converts the control string.
	@brief The function converts the control string `cap` to a control string that
		moves the capacity to the specified position (usually the cursor but
		there are other use cases like the color of the cursor).
	@note//_PARAMETERS
	@param cap The capability name, retrieved from the Terminfo entry with
		`tgetstr`.
	@param col The column of the cursor.
	@param row The row of the cursor.
	@note//_RETURNS
	@return A pointer to a control string that moves the cursor to the specified
		position or NULL if the capability is not avaliable.
 */
char			*tgoto(const char *cap, int col, int row);

/**
	@note//_DESCRIPTION
	@brief #### Sends a control string to the terminal.
	@brief The function sends the control string `str` to the terminal using the
		function `putc` to output the characters.
	@note//_PARAMETERS
	@param str The control string that moves the capability to the specified
		position.
	@param affcnt The number of lines affected by the control string, if unsure
		use 1.
	@param putc The function to be used to output the characters of the control
		string.
	@note//_RETURNS
	@return OK if the function succeeds, or ERR if an error occurred.
	@note//_NOTES
	@note `affcnt` is needed when the control string needs time to be executed,
		like when the whole window is cleared, that way there will not be any
		overlap between the control strings.
 */
int				tputs(const char *str, int affcnt, int (*putc)(int));
#endif /* notes.h */
