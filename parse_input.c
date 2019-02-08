#include "minishell.h"

int		unescaped_char(char *input, char c)
{
	int	i;
	int	counter;
	int	index;

	i = -1;
	counter = 0;
	index = 0;
	while (input && input[++i])
	{
		if (input[i] == c)
		{
			index = i;
			counter++;
		}
	}
	if (counter % 2 == 0)
		return (-1);
	return (index);
}

int		check_in_between(char *input, int index, char unescaped)
{
	int		i;
	int		start;
	int		end;
	char	escaped;

	start = -1;
	end = -1;
	i = -1;
	escaped = (unescaped == '\'') ? ('\"') : ('\'');
	while (input[++i])
	{
		if (input[i] == escaped)
		{
			start = i++;
			while (input[i] && input[i] != escaped)
				i++;
		}
		if (input[i] == escaped)
		{
			end = i++;
			while (input[i] && input[i] != escaped)
				i++;
		}
		if (start < index && index < end)
			return (1);
	}
	return (0);
}

void	check_unescaped(char *input)
{
	int		quotes;
	int		double_quotes;
	char	*line;
	char	unescaped_c;
	int		index;

	line = NULL;
	quotes = unescaped_char(input, '\'');
	double_quotes = unescaped_char(input, '\"');
	index = 0;
	if (quotes != double_quotes)
	{
		if (quotes == -1 || double_quotes == -1)
			unescaped_c = (quotes < double_quotes) ? ('\"') : ('\'');
		else
			unescaped_c = (quotes > double_quotes) ? ('\"') : ('\'');
		index = unescaped_char(input, unescaped_c);
		while (line == NULL || unescaped_char(line, unescaped_c) == -1)
		{
			if (check_in_between(input, index, unescaped_c))
				break;
			line != NULL ? input = strjoin_more(3, input, "\n", line) : 0;
			ft_printf("> ");
			get_next_line(0, &line);
		}
		(line != NULL) ? (input = strjoin_more(3, input, "\n", line)) : (0);
		(line != NULL) ? (free(line)) : (0);
	}
}

/*
** the line in the command line (g_input) gets split into an array of single
** words. The '~' and the variables declared with a '$' get replaced by the
** corresponding values.
** !!! if one word in the command line contains multiple variables with a '$'
** or a '~', only the first one gets replaced. !!!
*/

int		nbr_strchr(char *string, char c)
{
	int	i;
	int	nbr_occurances;

	i = -1;
	nbr_occurances = 0;
	while (string[++i])
	{
		if (string[i] == c)
			nbr_occurances++;
	}
	return (nbr_occurances);
}

void	split_seperate_cmds(t_input *input)
{
	int		i;
	int		j;
	int		nbr_cmds;
	int		length;

	i = -1;
	j = -1;
	nbr_cmds = nbr_strchr(input->input_string, ';') + 1;
	input->cmds = (char ***)malloc(sizeof(char **) * (nbr_cmds + 1));
	while (input->input_string[++i])
	{
		j++;
		while (input->input_string[i] == ' ')
			i++;
		if ((length = ft_strstr_index(&input->input_string[i], ";")) == -1)
			length = (int)ft_strlen(&input->input_string[i]);
		input->cmds_strings[j] = ft_strsub(input->input_string, i, length);
		input->cmds[j] = ft_strsplit_whitespace(input->cmds_strings[j]);
		while (input->input_string[i] && input->input_string[i] != ';')
			i++;
	}
	input->cmds[++j] = NULL;
}

void	get_args(t_input *input)
{
	int		i;
	int		j;
	char	*key;

	i = -1;
	check_unescaped(input->input_string);
	split_seperate_cmds(input);
	while (input->cmds && input->cmds[++i])
	{
		j = -1;
		while (input->cmds && input->cmds[i][++j])
		{
			while (ft_strchr(input->cmds[i][j], '~'))
			{
				if ((key = get_key(g_environ, "HOME")) != NULL)
					replace(&input->cmds[i][j], "~", key);
			}
			while (ft_strchr(input->cmds[i][j], '$'))
				dollar_extension(&input->cmds[i][j]);
		}
	}
}
