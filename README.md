# minishell 

[![asciicast](https://asciinema.org/a/zNuncJUbNNAWSPCFSMNVaFCPi.svg)](https://asciinema.org/a/zNuncJUbNNAWSPCFSMNVaFCPi)

## About
Minishell is a 42 school project of the Unix branch. The requirements were simple: build your own shell. The restrictions were similar to all our school projects:
 - only a few functions from the standard library can be used (-> hence my own version of the standard library (libft))
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
 - is has to be done in C
 - it needs to compile with the compiler flags -Wall -Wextra -Werror
 - a series of the builtins has to be implemented: echo, cd, env, setenv, unsetenv
 - the usage of errno was not allowed
 - the binary must be named minishell and has to compile with a Makefile
 
 ### Installation
 Clone the repository 
    `git clone https://github.com/cmicheledelaney/minishell.git`,
 change into the `minishell` directory and
 run the `make` command to compile the executable.
 After building the executable, run it with
    `./minishell`.
