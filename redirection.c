#include "minishell.h"
#include <fcntl.h>


int	redirect(t_input *input, int j, char **cmd)
{
	int		in;
	int		out;
	int		pid;
	char	*filename;

	filename = input->cmds[j][2];
	if (ft_strchr(input->input_string, '>') == NULL)
		return (0);
	pid = fork();
	in = (input->cmds[j][1][0] == '<') ? (open(filename, O_RDONLY)) : (0);
	out = (input->cmds[j][1][0] == '>') ? (open(filename, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) : (0);
	if (pid == -1)
		return(0);
	else if (pid == 0)
	{
		if (in)
		{
			int fd0 = open("s", O_RDONLY, 0);
			dup2(fd0, STDIN_FILENO);
			close(fd0);
			in = 0;
		}
		if (out)
		{
			dup2(out, 1);
			close(out);
			execvp(cmd[0], cmd);
			out = 0;
			exit(0);
		}
		//execvp(test[0], test);
		perror("execvp");
		_exit(1);
	}
	else
	{
		waitpid(pid, 0, 0);
	}
	return (1);
}
