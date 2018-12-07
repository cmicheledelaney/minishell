/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setenv_unsetenv.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:10:52 by ccodiga           #+#    #+#             */
/*   Updated: 2019/01/17 12:45:04 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** the three function env, setenv and unsetenv deal with the environment
** variables in g_environ (initially a copy of environ). env displays the array
** of g_environ, with setenv a new variabele can get added and with unsetenv
** a variable gets deleted.
** env SYNTAX: env
*/

int		ft_env(char **args)
{
	int i;

	args += 0;
	i = -1;
	while (g_environ[++i] != NULL)
		ft_printf("%s\n", g_environ[i]);
	return (0);
}

/*
** setenv adds or changed a variable in g_environ.
** SYNTAX: setenv [variable_name] [value]
** iterates through g_environ, searches for the variable and changes it's
** value to the specified value. If no such variable could be found in
** g_environ a new one will get added to the array.
*/

int		ft_setenv(char **args)
{
	int		i;
	char	**new_env;

	i = -1;
	if (args[1] == NULL || args[2] == NULL)
		return (0);
	if (get_key(g_environ, args[1]) != NULL)
	{
		change_key(args[1], args[2]);
		return (0);
	}
	while (g_environ[++i])
		;
	new_env = NULL;
	new_env = copy_array(g_environ);
	free_array(g_environ);
	g_environ = new_env;
	free(g_environ[i]);
	g_environ[i] = strjoin_more(3, args[1], "=", args[2]);
	return (0);
}

/*
** frees the deleted variable and moves all elements of the array one down.
*/

void	move_elements_in_array(char **array, int index)
{
	free(array[index]);
	while (array[index])
	{
		array[index] = array[index + 1];
		index++;
	}
}

/*
** deletes the variable defined in the command. Iterates through the
** array and compares the given variable with the existing variables in
** g_environ. If the given variable exists it will get deleted, otherwise
** an error message  gets printed.
** SYNTAX: unsetenv [variable_name]
*/

int		ft_unsetenv(char **args)
{
	int		unset_var;
	char	*variable;

	if (args[1] == NULL)
		return (0);
	variable = ft_strjoin(args[1], "=");
	unset_var = search_str_in_array(g_environ, variable);
	if (unset_var != -1)
		move_elements_in_array(g_environ, unset_var);
	else
		ft_printf("%s: no such environment variable\n", args[1]);
	free(variable);
	return (0);
}
