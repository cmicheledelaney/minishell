/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:17:18 by ccodiga           #+#    #+#             */
/*   Updated: 2019/01/17 17:00:29 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** reimplementation of the cd builtin. First the key for the HOME variable in
** the environment variables gets looked up, in case no arguments are given to
** the cd command. If a desired directory is specified, the current directory
** gets changed with chdir(). The PWD and OLDPWD variables in g_environ get
** updated.
*/

int	ft_cd(char **args)
{
	int		index;
	char	*pwd;
	char	*oldpwd;
	long	size;

	index = search_str_in_array(g_environ, "HOME");
	if ((args[1] == NULL || args[1][0] == '\0') && index != -1)
		chdir(g_environ[index] + 5);
	else if (args[1] != NULL && !ft_strcmp(args[1], "-"))
		chdir(get_key(g_environ, "OLDPWD"));
	else if ((index == -1 && args[1] == NULL) || chdir(args[1]) != 0)
	{
		(index == -1) ? (ft_printf("%s", "HOME")) : (ft_printf("%s", args[1]));
		ft_printf(": not a directory\n");
	}
	if ((oldpwd = get_key(g_environ, "PWD")) != NULL)
		change_key("OLDPWD", oldpwd);
	size = 1000;
	pwd = NULL;
	if ((pwd = (char *)malloc((size_t)size)) != NULL)
		pwd = getcwd(pwd, (size_t)size);
	change_key("PWD", pwd);
	(pwd != NULL) ? (free(pwd)) : (0);
	return (1);
}

/*
** exits the minishell.
*/

int	ft_exit(char **args)
{
	args += 0;
	free_array(g_environ);
	return (-1);
}

/*
** prints everything that follows to the terminal. If the desired output gets
** passed as one string (in "") the output keeps the spaces, otherwise each
** word is seperated by exactly one space.
*/

int	ft_echo(char **args)
{
	char	*str;
	int		last_char;
	int		i;

	i = 0;
	last_char = -1;
	while (g_input[++last_char])
		;
	if ((args)[1] != NULL)
	{
		if (g_input[5] == '"' && g_input[last_char - 1] == '"')
		{
			str = ft_strsub(g_input, 6, ft_strlen(g_input) - 7);
			ft_printf("%s", str);
			free(str);
		}
		else
		{
			while (args[++i])
				ft_printf("%s ", args[i]);
		}
		ft_printf("\n");
	}
	return (0);
}
