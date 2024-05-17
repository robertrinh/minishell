<h1 align="center">
	Functions
</h1>

[link to pipex](https://github.com/QBeukelman/pipex/tree/master)

## pipe (int fildes[2])

Returns two open file descriptos, each for `read[0]` and `write[1]` ends of the pipe. Sends the output of the first `execve()` as input to the second `execve()`.

<br />



## fork (void)

Fork creates a new process. The child process is an exact copy of the parent, except for:

* Unique ID
* Diferent parent
* Own copy of parents descriptors

**Return:** A value of 0 to the child process and the process ID of the child process to the parent process.

<br />



## dup(int fildes) and dup2(int fildes, int fildes2)

Duplicates an existing object descriptor and returns its value to the calling process (fildes2 = dup(fildes)). In `dup2()`, the value of the new descriptor fildes2 is specified.

<br />



## waitpid(pid_t pid, int *stat_loc, int options)

Suspends execution of its calling process untill stat_loc information is availavle for the terminated child process, or a signal is recieved.

The `pid` argument enables the selection of a child process to be waited for.

<br />



## execve(const char *path, char *const argv[], char *const envp[])

Load a new program with params, `pathname`, `argv`, `envp`, into a process memory. The stack, data and heap are freshly created for the program.

<br />



## access(const char *path, int mode)

Checks the a11y of the file named by the `path` argument for the access permission inficated by the `mode` argument. Return `0` on success.

<br />

