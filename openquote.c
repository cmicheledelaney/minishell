#include "minishell.h"

/*
** checks if the string contains a character, a quote for example, that
** hasn't been closed. it returns the value of the index of the the
** character that hasn't been closed. otherwise it returns -1.
*/

int		openquote_index(char *input, char c)
{
	int	i;

	i = -1;
	while (input && input[++i])
	{
		if (input[i] == c &&
			!is_in_between(input, i, QUOTES) &&
			!is_in_between(input, i, DOUBLEQUOTES))
			return (i);
	}
	return (-1);
}

/*
** checks if an index is surrounded by a character (char embrace). Embrace
** doesn't need to surround the index directly. if it is surrounded by the
** embrace, it returns 1, otherwise 0.
*/

int		is_in_between(char *input, int index, char embrace)
{
	int		i;
	int		start;
	int		end;
	int		max;

	max = strlen(input);
	start = -1;
	end = -1;
	i = -1;
	while (++i < max)
	{
		if (start == -1 && input[i] == embrace)
			start = i++;
		if (end == -1 && input[i] == embrace)
			end = i++;
		if (i <= max && start < index && index < end)
			return (1);
		else if (start != -1 && end != -1)
		{
			start = -1;
			end = -1;
		}
	}
	return (0);
}

/*
** reads through the string and checks for unclosed quotes/double quotes. if
** there are any, it keeps reading until the quote/double quote gets closed.
*/

void	check_for_openquotes(t_input  *input)
{
	int		quotes;
	int		double_quotes;
	char	*line;
	char	unescaped_c;
	int		index;

	line = NULL;
	quotes = openquote_index(input->input_string, '\'');
	double_quotes = openquote_index(input->input_string, '\"');
	index = 0;
	if (quotes != double_quotes)
	{
		if (quotes == -1 || double_quotes == -1)
			unescaped_c = (quotes < double_quotes) ? ('\"') : ('\'');
		else
			unescaped_c = (quotes > double_quotes) ? ('\"') : ('\'');
		index = openquote_index(input->input_string, unescaped_c);
		while (line == NULL || openquote_index(line, unescaped_c) == -1)
		{
			ft_printf("> ");
			get_next_line(0, &line);
			line != NULL ? input->input_string = strjoin_more(3, input->input_string, "\n", line) : 0;
			input->input_string = convert_quotes(input->input_string, '\'', '\"', QUOTES);
			input->input_string = convert_quotes(input->input_string, '\"', QUOTES, DOUBLEQUOTES);
			if (is_in_between(input->input_string, index,(unescaped_c == QUOTES) ? (QUOTES) : (DOUBLEQUOTES)))
				break;
		}
		(line != NULL) ? (input->input_string = strjoin_more(3, input->input_string, "\n", line)) : (0);
		(line != NULL) ? (free(line)) : (0);
	}
}

/*
** iterates through the string and counts how often the character c appears in
** it. it only counts the characters that are not closed in between quotes or double
** quotes.
*/

int		nbr_unquoted_char(char *string, char c)
{
	int	i;
	int	nbr_occurances;

	i = -1;
	nbr_occurances = 0;
	while (string[++i])
	{
		if (string[i] == c &&
			!is_in_between(string, i, QUOTES) &&
			!is_in_between(string, i, DOUBLEQUOTES))
			nbr_occurances++;
	}
	return (nbr_occurances);
}

/*
** iterates through the given string and looks for the character seperator. it
** returns the index of it if it is not enclosed by quotes or double quotes.
*/

int		find_index_of_next_unembraced_seperator(char *string, char seperator)
{
	int	i;
	int	index;

	i = -1;
	index = -1;
	while (string[++i])
	{
		index = ft_strchr_index(&string[i], seperator) + i;
		if (index != -1 &&
			!is_in_between(string, index, QUOTES) &&
			!is_in_between(string, index, DOUBLEQUOTES))
			return (index);
		if (index == -1)
			return (-1);
	}
	return (-1);
}
