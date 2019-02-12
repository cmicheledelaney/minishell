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
	while (input->input_string && input->input_string[++i])
	{
		while ((index = ft_strchr_index(input->input_string, '~')) != -1
			&& check_in_between(input->input_string, index, QUOTES) == 0)
		{
			if ((key = get_key(g_environ, "HOME")) != NULL)
				replace(&input->input_string, "~", key);
		}
		while ((index = ft_strchr_index(input->input_string, '$')) != -1
			&& check_in_between(input->input_string, index, QUOTES) == 0)
		{
			dollar_extension(&input->input_string);
		}
	}
}

int		unescaped_char(char *input, char c)
{
	int	i;

	i = -1;
	while (input && input[++i])
	{
		if (input[i] == c &&
			!check_in_between(input, i, QUOTES) &&
			!check_in_between(input, i, DOUBLEQUOTES))
			return (i);
	}
	return (-1);
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
/*
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
*/

void	check_unescaped(t_input  *input)
{
	int		quotes;
	int		double_quotes;
	char	*line;
	char	unescaped_c;
	int		index;

	line = NULL;
	quotes = unescaped_char(input->input_string, '\'');
	double_quotes = unescaped_char(input->input_string, '\"');
	index = 0;
	if (quotes != double_quotes)
	{
		if (quotes == -1 || double_quotes == -1)
			unescaped_c = (quotes < double_quotes) ? ('\"') : ('\'');
		else
			unescaped_c = (quotes > double_quotes) ? ('\"') : ('\'');
		index = unescaped_char(input->input_string, unescaped_c);
		while (line == NULL || unescaped_char(line, unescaped_c) == -1)
		{
			ft_printf("> ");
			get_next_line(0, &line);
			line != NULL ? input->input_string = strjoin_more(3, input->input_string, "\n", line) : 0;
			input->input_string = convert_quotes(input->input_string, '\'', '\"', QUOTES);
			input->input_string = convert_quotes(input->input_string, '\"', QUOTES, DOUBLEQUOTES);
			if (check_in_between(input->input_string, index,(unescaped_c == QUOTES) ? (QUOTES) : (DOUBLEQUOTES)))
				break;
		}
		(line != NULL) ? (input->input_string = strjoin_more(3, input->input_string, "\n", line)) : (0);
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
			!check_in_between(string, i, QUOTES) &&
			!check_in_between(string, i, DOUBLEQUOTES))
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
			!check_in_between(string, index, QUOTES) &&
			!check_in_between(string, index, DOUBLEQUOTES))
			return (index);
		else
		{
			if (index == -1)
				return (index);
		}
	}
	return (-1);
}

void	remove_quotes(t_input *input)
{
	int	i;
	int	j;
	int	index;

	i = -1;
	while (input->cmds[++i])
	{
		j = -1;
		while (input->cmds[i][++j])
		{
			while ((index = ft_strchr_index(input->cmds[i][j], QUOTES))!= -1 ||
				(index = ft_strchr_index(input->cmds[i][j], DOUBLEQUOTES)) != -1)
			{
				int m = index -1;
				while (input->cmds[i][j][++m] && input->cmds[i][j][m + 1])
					input->cmds[i][j][m] = input->cmds[i][j][m + 1];
				input->cmds[i][j][m] = '\0';
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

void	set_to_neg_one(int *one, int *two)
{
	*one = -1;
	*two = -1;
}

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

void	get_args(t_input *input)
{
	int	i;
	int	nbr_cmds;

	i = -1;
	input->input_string = convert_quotes(input->input_string, '\'', '\"', QUOTES);
	input->input_string = convert_quotes(input->input_string, '\"', QUOTES, DOUBLEQUOTES);
	nbr_cmds = nbr_strchr_unembraced(input->input_string, ';') + 2;
	input->cmds_strings = (char **)malloc(sizeof(char *) * nbr_cmds);
	input->cmds = (char ***)malloc(sizeof(char **) * (nbr_cmds + 100)); //look at this again, something's wrong
	check_unescaped(input);
	first_step(input);
	split_cmds(input->cmds_strings, input->input_string, ';');
	while (input->cmds_strings[++i])
	{
		nbr_cmds = nbr_strchr_unembraced(input->cmds_strings[i], ' ') + 2;
		input->cmds[i] = (char **)malloc(sizeof(char *) * nbr_cmds);
		split_cmds(input->cmds[i], input->cmds_strings[i], ' ');
	}
	remove_quotes(input);
	remove_quotes(input);
}
