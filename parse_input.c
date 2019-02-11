#include "minishell.h"

/*
** the parsing hierarchy is as follows:
** quotes/doublequotes, pipes, redirection, semi-colon, spaces.
** something that is surrounded by quotes or double quotes, won't get parsed
** any further.
*/


/*
** checks if there are things to replace (if there is a $ or ~ not in between
** single quotes) and replaces them accordingly.
** DOESN'T WORK IN CASES LIKE THIS: $HOME$HOME
*/

void	first_step(t_input *input)
{
	int		i;
	char	*key;
	int		index;

	i = -1;
	check_unescaped(input->input_string);
	while (input->input_string && input->input_string[++i])
	{
		while ((index = ft_strchr_index(input->input_string, '~')) != -1
			&& check_in_between(input->input_string, index, '\'') == 0)
		{
			if ((key = get_key(g_environ, "HOME")) != NULL)
				replace(&input->input_string, "~", key);
		}
		while ((index = ft_strchr_index(input->input_string, '$')) != -1
			&& check_in_between(input->input_string, index, '\'') == 0)
		{
			dollar_extension(&input->input_string);
		}
	}
}

/*
** splits the input into the pieces that are embraced by quotes.
*/

/*char	**parse_embraced_tokens(char *input, char embrace, char no_embraced)
{
	char **args;
	int		start;
	int		nbr;

	start = -1;
	nbr = -1;
	args = (char **)malloc(sizeof(char *) * 1000);
	while (input[++i])
	{
		if (input[i] == embrace &&
			!check_in_between(input, i, no_embraced))
		{
			(start == -1) ? (start = i) : (0);
		}
		if (start != -1)
		{
			args[++nbr] = ft_strsub(input, start, end - i);
			start = -1;
		}
	}
	args[++nbr] = NULL;
	return (args);
}

void	second_step(t_input input)
{
	char	**args;
	int		i;

	i = -1;
	//first parse the quotes
	args = parse_embraced_tokens(input->input_string, '\'', '\"');
	//then parse double quotes
	while (args[++i])
		parse_embraced_tokens(args[i], '\'', '\"');*/

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

int		check_in_between(char *input, int index, char embrace)
{
	int		i;
	int		start;
	int		end;
	int		max;

	max = ft_strlen(input);
	start = -1;
	end = -1;
	i = -1;
	while (++i < max)
	{
		if (input[i] == embrace)
		{
			start = i++;
			while (input[i] && input[i] != embrace)
				i++;
		}
		if (input[i] == embrace)
		{
			end = i++;
			while (input[i] && input[i] != embrace)
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
			if (check_in_between(input, index,(unescaped_c == '\'') ? ('\"') : ('\'')))
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

int		nbr_strchr_unembraced(char *string, char c)
{
	int	i;
	int	nbr_occurances;

	i = -1;
	nbr_occurances = 0;
	while (string[++i])
	{
		if (string[i] == c &&
			!check_in_between(string, i, '\'') &&
			!check_in_between(string, i, '\"'))
			nbr_occurances++;
	}
	return (nbr_occurances);
}

int		find_index_of_next_unembraced_seperator(char *string, char seperator)
{
	int	i;
	int	index;

	i = -1;
	index = -1;
	while (string[++i])
	{
		index = ft_strchr_index(string, seperator);
		if (index != -1 &&
			!check_in_between(string, index, '\'') &&
			!check_in_between(string, index, '\"'))
			return (index);
		else
		{
			if (index == -1)
				return (index);
		}
	}
	return (-1);
}

void	remove_quotes(t_input *input, char sign)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	while (input->cmds[++i])
	{
		j = -1;
		while (input->cmds[i][++j])
		{
			k = -1;
			while (input->cmds[i][j][++k])
			{
				if (input->cmds[i][j][k] == sign)
				{
					int m = k -1;
					while (input->cmds[i][j][++m] && input->cmds[i][j][m + 1])
						input->cmds[i][j][m] = input->cmds[i][j][m + 1];
					input->cmds[i][j][m] = '\0';
				}
			}
		}
	}
}

void	split_cmds(char **args, char *string, char split)
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

void	get_args(t_input *input)
{
	int	i;
	int	nbr_cmds;

	i = -1;
	nbr_cmds = nbr_strchr_unembraced(input->input_string, ';') + 2;
	input->cmds_strings = (char **)malloc(sizeof(char *) * nbr_cmds);
	input->cmds = (char ***)malloc(sizeof(char **) * (nbr_cmds + 100)); //look at this again, something's wrong
	check_unescaped(input->input_string);
	first_step(input);
	split_cmds(input->cmds_strings, input->input_string, ';');
	while (input->cmds_strings[++i])
	{
		nbr_cmds = nbr_strchr_unembraced(input->cmds_strings[i], ' ') + 2;
		input->cmds[i] = (char **)malloc(sizeof(char *) * nbr_cmds);
		split_cmds(input->cmds[i], input->cmds_strings[i], ' ');
	}
	remove_quotes(input, '\'');
	remove_quotes(input, '\"');
}
