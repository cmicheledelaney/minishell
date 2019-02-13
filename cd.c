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

//updating of OLDPWD doesn't work

int	ft_cd(t_input *input, int j)
{
	int		index;
	char	*pwd;
	char	*oldpwd;
	long	size;

	index = search_str_in_array(g_environ, "HOME");
	if ((input->cmds[j][1] == NULL || input->cmds[j][1][0] == '\0') && index != -1)
		chdir(g_environ[index] + 5);
	else if (input->cmds[j][1] != NULL && !ft_strcmp(input->cmds[j][1], "-"))
		chdir(get_key(g_environ, "OLDPWD"));
	else if ((index == -1 && input->cmds[j][1] == NULL) || chdir(input->cmds[j][1]) != 0)
	{
		(index == -1) ? (ft_printf("%s", "HOME")) : (ft_printf("%s", input->cmds[j][1]));
		ft_printf(": not a directory\n");
	}
	if ((oldpwd = get_key(g_environ, "PWD")) != NULL)
		change_key("OLDPWD", oldpwd);
	size = 1000;
	pwd = NULL;
	if ((pwd = (char *)malloc(sizeof(char) * size)) != NULL)
		pwd = getcwd(pwd, (size_t)size);
	change_key("PWD", pwd);
	free(pwd);
	return (1);
}
