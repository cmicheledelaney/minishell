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
** checks if there are things to replace (if there is a $ or ~ not in between
** single quotes) and replaces them accordingly.
*/

void	expansions(t_input *input, int i)
{
	int	j;
	char	*key;
	int	index;

	j = -1;
	while (input->cmds[i] && input->cmds[i][++j])
	{
		while ((index = ft_strchr_index(input->cmds[i][j], '~')) != -1
			&& !is_in_between(input->cmds[i][j], index, QUOTES))
		{
			if ((key = get_key(g_environ, "HOME")) != NULL)
				replace(&input->cmds[i][j], "~", key);
		}
		while ((index = ft_strchr_index(input->cmds[i][j], '$')) != -1
			&& !is_in_between(input->cmds[i][j], index, QUOTES))
		{
			dollar_expansion(&input->cmds[i][j]);
		}
	}
}

/*
** goes through the variable with the '$' extension and replaces it with the
** corresponding value, if the variable is set in g_environ. Otherwise the
** variable gets replaced with '\0'.
*/

void	dollar_expansion(char **args)
{
	size_t	start_var;
	char	*variable;
	size_t	end_var;
	size_t	check_quotes;

	start_var = ft_strlen_char(*args, '$');
	end_var = ft_strlen_char(&(*args)[start_var], '/');
	check_quotes = ft_strlen_char(&(*args)[start_var], QUOTES);
	end_var = (check_quotes > end_var) ? (end_var) : (check_quotes);
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
	int		i;
	char	**new_env;

	i = -1;
	if (variable == NULL || key== NULL)
		return ;
	if ((unset_var = search_str_in_array(g_environ, variable)) == -1)
	{
		while (g_environ[++i])
			;
		unset_var = i;
	}
	new_env = copy_array(g_environ);
	free_array(g_environ);
	g_environ = new_env;
	(g_environ[unset_var] != NULL) ? (free(g_environ[unset_var])) : (0);
	g_environ[unset_var] = strjoin_more(3, variable, "=", key);
}
