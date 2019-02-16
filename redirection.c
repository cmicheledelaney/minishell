#include "minishell.h"
#include <fcntl.h>


int	redirect(t_input *input, int j, char **cmd, int i, int in, int out)
{
	char	*filename;

	filename = input->cmds[j][i + 1];
	if (filename == NULL)
	{
		printf("filename is missing\n");
		return (-1);
	}
	in = (input->cmds[j][i][0] == '<') ? (open(filename, O_RDONLY)) : (STDIN_FILENO);
	out = (input->cmds[j][i][0] == '>') ? (open(filename, O_WRONLY | O_TRUNC |
		O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) : (STDOUT_FILENO);
	if (in) // when '<' occurs
	{
		dup2(in, STDIN_FILENO);
		close(in);
		(i < 3) ? (execvp(cmd[0], cmd)) : (0);
		in = 0;
		exit(0);
	}
	if (out) // when '>' occurs
	{
		dup2(out, STDOUT_FILENO);
		close(out);
		(i < 3) ? (execvp(cmd[0], cmd)) : (0);
		out = 0;
		exit(0);
	}
	return (1);
}
