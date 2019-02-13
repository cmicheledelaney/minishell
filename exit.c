#include "minishell.h"


/*
** exits the minishell.
*/

int	ft_exit(t_input *input, int j)
{
	input->cmds[j] += 0;
	free_array(g_environ);
	return (-1);
}
