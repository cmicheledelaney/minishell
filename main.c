/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:05:01 by ccodiga           #+#    #+#             */
/*   Updated: 2019/02/13 12:17:29 by ccodiga          ###   ########.fr       */
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

int		(*g_builtin_functions[])(t_input *, int) =
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

char	*check_access(char **cmd, char **array)
{
	int		i;
	char	*access_str;
	char	*hold;

	i = -1;
	while (array[++i])
	{
		if (i == 0)
			access_str = ft_strdup(cmd[0]);
		else
		{
			access_str = ft_strjoin(array[i], "/");
			hold = access_str;
			access_str = ft_strjoin(access_str, cmd[0]);
			free(hold);
		}
		if (access(access_str, X_OK) == 0)
			return (access_str);
		else
			free(access_str);
	}
	return (NULL);
}


char	*get_access_string(char **cmd)
{
	int		path_key;
	char	*valid_access;
	char	**paths;

	path_key = search_str_in_array(g_environ, "PATH");
	if (path_key == -1 && access(cmd[0], X_OK))
	{
		ft_printf("PATH not found\n");
		return (NULL);
	}
	paths = (path_key != -1) ? (ft_strsplit(g_environ[path_key] + 5, ':')) : (NULL);
	valid_access = (path_key != -1) ? (check_access(cmd, paths)) : (ft_strdup(cmd[0]));
	if (valid_access == NULL)
		ft_printf("command not found: %s\n", cmd[0]);
	(paths != NULL) ? (free_array(paths)) : (0);
	return (valid_access);
}


/*
** getting an array of the different paths in the PATH variable, which then
** will get passed to check_acces, to get the right absolut path of the
** executable. The returned string contains the path joined with the name
** of the executable, shich then will be passed into the execve function.
** The execve function executes the command as a child process.
*/

int		run_commands(char **cmd)
{
	/*int		path_key;
	char	*valid_access;
	char	**paths;

	path_key = search_str_in_array(g_environ, "PATH");
	if (path_key == -1 && access(cmd[0], X_OK))
	{
		ft_printf("PATH not found\n");
		return (-1);
	}
	paths = (path_key != -1) ? (ft_strsplit(g_environ[path_key] + 5, ':')) : (NULL);
	valid_access = (path_key != -1) ? (check_access(cmd, paths)) : (ft_strdup(cmd[0]));
	if (valid_access == NULL)
		ft_printf("command not found: %s\n", cmd[0]);
	*/
	char *valid_access = get_access_string(cmd);
	if (valid_access != NULL && (g_pid_child = fork()) == 0)
		execve(valid_access, cmd, g_environ);
	else
		wait(NULL);
	(valid_access != NULL) ? (free(valid_access)) : (0);
	//(paths != NULL) ? (free_array(paths)) : (0);
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

int		exec_cmd(t_input *input, int j)
{
	int	done;
	int	i;

	done = 0;
	i = -1;
	while (input->cmds != NULL && input->cmds[j][0] && g_builtin[++i])
	{
		if (ft_strcmp(input->cmds[j][0], g_builtin[i]) == 0)
		{
			done = 1;
			if (g_builtin_functions[i](input, j) == -1)
				exit(0);
		}
	}
	if (done == 0 && input->cmds[j][0] != NULL)
		return (1);
	return (0);
}


int		minishell(void)
{
	t_input	input;
	int		j;

	while (print_prompt() && get_next_line(0, &input.input_string) > 0)
	{
		get_args(&input);
		j = -1;
		while (input.cmds[++j])
		{
			if (check_for_pipe(&input, j) == 1)
				continue;
			if (exec_cmd(&input, j))
				run_commands(input.cmds[j]);
			//free_array(input.cmds[j]); something is wrong here
			free(input.cmds_strings[j]);
		}
		(input.input_string != NULL) ? (free(input.input_string)) : (0);
		input.input_string = NULL;
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
		g_pid_child = 0;
	ft_printf("\n");
	return (0);
	}
