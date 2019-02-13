#include "minishell.h"

void	remove_char(t_input *input, int i, char c)
{
	int	j;
	int	index;

	j = -1;
	while (input->cmds[i][++j])
	{
		while ((index = ft_strchr_index(input->cmds[i][j], c))!= -1)
		{
			int m = index -1;
			while (input->cmds[i][j][++m] && input->cmds[i][j][m + 1])
				input->cmds[i][j][m] = input->cmds[i][j][m + 1];
			input->cmds[i][j][m] = '\0';
		}
	}
}

/*
**split_strings a string into an array. the string getssplit_string by the charactersplit_string,
** but only if thatsplit_string is not within quotes/double quotes.
*/

void	split(char **args, char *string, char split)
{
	int		i;
	int		j;
	int		length;
	int		max;

	i = -1;
	j = -1;
	max = (string != NULL) ? (ft_strlen(string)) : (0);
	while (++i < max)
	{
		while (string[i] == ' ')
			i++;
		if ((length = find_index_of_next_unembraced_seperator(&string[i], split)) == -1)
		{
			length = (int)ft_strlen(&string[i]);
		}
		args[++j] = ft_strsub(string, i, length);
		i = i + length;
	}
	args[++j] = NULL;
}

void	set_to_neg_one(int *one, int *two)
{
	*one = -1;
	*two = -1;
}

/*
** the quotes/double quotes in the string that are closed and not just simple characters
** get set to the value -1 for quotes and -2 for double quotes (defined in header).
*/

char	*convert_quotes(char *input, char quotes, char other, char conversion_value)
{
	int	i;
	int	start;
	int	start_o;

	set_to_neg_one(&start, &start_o);
	i = -1;
	while (++i < (int)ft_strlen(input))
	{
		(input[i] == quotes && start == -1) ? (start = i++) : (0);
		(input[i] == other && start_o == -1) ? (start_o = i++) : (0);
		if (input[i] == quotes &&
			start != -1 && (start_o == -1 ||
			start_o > start))
		{
			input[i] = conversion_value;
			input[start] = conversion_value;
			set_to_neg_one(&start, &start_o);
		}
		if (input[i] == other && start_o != -1 &&
			(start == -1 || start_o < start))
			set_to_neg_one(&start, &start_o);
		
	}
	return (input);
}

/*
** at this point one line has been read. The quotes/double quotes get converted
** to the values -1 and -2. the string getssplit_string into an array of cmds, seperated
** by ';'. the elements of that array getsplit_string at the spaces into arrays of tokens.
** the doublequotes get removed, the expansion get replaced with their values and
** at the end the quotes get removed.
*/

void	get_args(t_input *input)
{
	int	i;
	int	nbr_cmds;

	i = -1;
	input->input_string = convert_quotes(input->input_string, '\'', '\"', QUOTES);
	input->input_string = convert_quotes(input->input_string, '\"', QUOTES, DOUBLEQUOTES);
	nbr_cmds = nbr_unquoted_char(input->input_string, ';') + 2;
	input->cmds_strings = (char **)malloc(sizeof(char *) * nbr_cmds);
	input->cmds = (char ***)malloc(sizeof(char **) * (nbr_cmds + 100)); //look at this again, something's wrong
	check_for_openquotes(input);
	split(input->cmds_strings, input->input_string, ';');
	while (input->cmds_strings[++i])
	{
		nbr_cmds = nbr_unquoted_char(input->cmds_strings[i], ' ') + 2;
		input->cmds[i] = (char **)malloc(sizeof(char *) * nbr_cmds);
		split(input->cmds[i], input->cmds_strings[i], ' ');
		remove_char(input, i, DOUBLEQUOTES);
		expansions(input, i);
		remove_char(input, i, QUOTES);
	}
}
