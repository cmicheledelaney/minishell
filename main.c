/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:05:01 by ccodiga           #+#    #+#             */
/*   Updated: 2019/01/18 09:59:08 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** names of the builtins implemented in this program. They are needed when the
** command gets redirected to the right function.
*/

char	*g_builtin[] =
{
	"cd",
	"exit",
	"setenv",
	"env",
	"unsetenv",
	"echo",
	NULL,
};

/*
** array of the builtins implemented in this program.
*/

int		(*g_builtin_functions[])(char **) =
{
	&ft_cd,
	&ft_exit,
	&ft_setenv,
	&ft_env,
	&ft_unsetenv,
	&ft_echo,
};

/*
** iterating through the different paths of the PATH variable and trying to
** access each path in combination with the name of the executable. When
** access returns 0 (executable is in this path), the string will be returned
** to the execve function.
*/

char	*check_access(char **args, char **array)
{
	int		i;
	char	*access_str;
	char	*hold;

	i = -1;
	while (array[++i])
	{
		if (i == 0)
			access_str = ft_strdup(args[0]);
		else
		{
			access_str = ft_strjoin(array[i], "/");
			hold = access_str;
			access_str = ft_strjoin(access_str, args[0]);
			free(hold);
		}
		if (access(access_str, X_OK) == 0)
			return (access_str);
		else
			free(access_str);
	}
	return (NULL);
}

/*
** getting an array of the different paths in the PATH variable, which then
** will get passed to check_acces, to get the right absolut path of the
** executable. The returned string contains the path joined with the name
** of the executable, shich then will be passed into the execve function.
** The execve function executes the command as a child process.
*/

int		run_commands(char **args)
{
	int		path_key;
	char	*valid_access;
	char	**paths;

	path_key = search_str_in_array(g_environ, "PATH");
	if (path_key == -1 && access(args[0], X_OK))
	{
		ft_printf("PATH not found\n");
		return (-1);
	}
	paths = (path_key != -1) ? (ft_strsplit(g_environ[path_key] + 5, ':')) : (NULL);
	valid_access = (path_key != -1) ? (check_access(args, paths)) : (ft_strdup(args[0]));
	if (valid_access == NULL)
		ft_printf("command not found: %s\n", args[0]);
	if (valid_access != NULL && (g_pid_child = fork()) == 0)
		execve(valid_access, args, g_environ);
	else
		wait(NULL);
	(valid_access != NULL) ? (free(valid_access)) : (0);
	(paths != NULL) ? (free_array(paths)) : (0);
	return (0);
}

/*
** reads the input given on the command line line by line and processes it.
** First the function pointer array will be searched for the command, if it's
** not found there, the command gets executed by run_commands.
*/

int		print_prompt(void)
{
	char *username;

	ft_printf(MAG "minishell " CYA2 "(%s) " WHI,
		(((username = get_key(g_environ, "USER")) == NULL) ?
		("-") : (username)));
	return (1);
}

void	exec_cmd(char ***args, int j)
{
	int	done;
	int	i;

	done = 0;
	i = -1;
	while (args != NULL && args[j][0] && g_builtin[++i])
	{
		if (ft_strcmp(args[j][0], g_builtin[i]) == 0)
		{
			done = 1;
			if (g_builtin_functions[i](args[j]) == -1)
				exit(0);
		}
	}
	(done == 0 && args[j][0] != NULL) ? (run_commands(args[j])) : (0);
}



int		minishell(void)
{
	char	***args;
	int		j;

	while (print_prompt() && get_next_line(0, &g_input) > 0)
	{
		args = get_args();
		j = -1;
		while (args[++j])
		{
			exec_cmd(args, j);
			free_array(args[j]);
		}
		(g_input != NULL) ? (free(g_input)) : (0);
		free(args);
		return (1);
	}
	return (0);
}

/*
** catches the signal SIGINT (ctrl + c) and exits the child process. If SIGINT
** is sent by the parent process it just returns to where the process got
** interrupted.
*/

void	signal_handler(int signum)
{
	if (g_pid_child != 0 && g_pid_child != g_pid_parent)
	{
		ft_printf("\n");
		kill(g_pid_child, signum);
	}
}

/*
** initializes the signal for SIGINT and starts the nearly infinite loop of the
** minishell while printing the prompt with the value of USER. The global for
** the parent process gets set and the global for the child process gets reset
** to zero each time a command has been executed (important for SIGINT).
** g_environ contains the environment variables. Only at the beginning of the
** program they get copied from environ, after they get changed by internal
** processes.
*/

int		main(int argc, char **argv, char **environ)
{
	g_pid_parent = getpid();
	argv[argc] = NULL;
	signal(SIGINT, signal_handler);
	g_environ = copy_array(environ);
	while (minishell())
	{
		g_input = NULL;
		g_pid_child = 0;
	}
	ft_printf("\n");
	return (0);
}
