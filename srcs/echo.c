#include "minishell.h"

/*
** prints everything that follows to the terminal. If the desired output gets
** passed as one string (in "") the output keeps the spaces, otherwise each
** word is seperated by exactly one space.
*/

int	ft_echo(t_input *input, int j)
{
	int		last_char;
	int		i;

	i = 0;
	last_char = -1;
	while (input->cmds_strings[j][++last_char])
		;
	if ((input->cmds)[j][1] != NULL)
	{
		while (input->cmds[j][++i])
			ft_printf("%s ", input->cmds[j][i]);
		ft_printf("\n");
	}
	return (0);
}
