/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_environ.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:49:15 by ccodiga           #+#    #+#             */
/*   Updated: 2019/01/17 17:03:43 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** goes through the variable with the '$' extension and replaces it with the
** corresponding value, if the variable is set in g_environ. Otherwise the
** variable gets replaced with '\0'.
*/

void	dollar_extension(char **args)
{
	size_t	start_var;
	size_t	end_var;
	char	*variable;

	start_var = ft_strlen_char(*args, '$');
	end_var = ft_strlen_char(&(*args)[ft_strlen_char(*args, '$')], '/');
	variable = ft_strsub(*args, start_var, end_var);
	replace(args, variable, get_key(g_environ, &variable[1]));
	free(variable);
}

/*
** iterates through the array dict and searches for the given variable.
** It's assumed that the values in dict are connected by a '=' and no spaces.
** It returnes a pointer to the key in dict (no memory will get allocated for
** the key!).
*/

char	*get_key(char **dict, char *variable)
{
	int		i;
	int		length;

	i = -1;
	length = ft_strlen(variable);
	variable = ft_strjoin(variable, "=");
	while (dict[++i])
	{
		if (ft_strstr_index(dict[i], variable) == 0)
		{
			free(variable);
			return (&dict[i][length + 1]);
		}
	}
	free(variable);
	return (NULL);
}

/*
** changes the value of the given variable if it already exists. Otherwise
** it passes it to the setenv function, which sets a new variable in
** g_environ.
*/

void	change_key(char *variable, char *key)
{
	int		unset_var;
	char	*array[3];

	array[0] = "";
	array[1] = variable;
	array[2] = key;
	if ((unset_var = search_str_in_array(g_environ, variable)) == -1)
	{
		ft_setenv(array);
		return ;
	}
	free(g_environ[unset_var]);
	g_environ[unset_var] = strjoin_more(3, variable, "=", key);
}
