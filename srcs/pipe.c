#include "minishell.h"

int		spawn_proc(int in, int out, char **cmd)
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		return (execvp(cmd[0], cmd)); //needs to get replaced with execv function
	}
	return (pid);
}

//algorithm is not completely working yet, redirections combined with pipes don't work
int		fork_pipes(t_input *input, int j)
{
	int		i;
	int		k;
	int		in;
	int		fd[2];
	int		index;
	char	**cmd;

	in = 0;
	i = -1;
	while (input->cmds[j][i] && input->cmds[j][++i])
	{
		index = 0;
		while (input->cmds[j][i + index] &&
			!IS_OPERATOR(input->cmds[j][i + index][0]))
			index++;
		cmd = (char **)malloc(sizeof(char *) * index + 1);
		k = -1;
		while (input->cmds[j][i] &&
			!IS_OPERATOR(input->cmds[j][i][0]))
			cmd[++k] = input->cmds[j][i++];
		cmd[++k] = NULL;
		if (input->cmds[j][i] == NULL)
			break;
		if (input->cmds[j][index][0] == '|')
		{
			pipe(fd);
			spawn_proc(in, fd[1], cmd);
			close(fd[1]);
			in = fd[0];
		}
		if (input->cmds[j][index][0] != '|')
		{
			redirect(input, j, cmd, i, in, fd[1])
		}
	}
	if (in != 0)
		dup2(in, 0);
	execvp(cmd[0], cmd); //needs to get replaced with execve function
	return (1);
}

/*
** checks if there are any pipes or redirections in the command. if so,
** it gets directed to fork_pipes.
*/

int		check_for_pipe(t_input *input, int j)
{
	pid_t	pid;

	if (ft_strchr(input->input_string, '|') == NULL &&
		ft_strchr(input->input_string, '>') == NULL &&
		ft_strchr(input->input_string, '<') == NULL)
		return (0);
	if ((pid = fork()) == 0)
		fork_pipes(input, j);
	wait(NULL);
	return (1);
}
