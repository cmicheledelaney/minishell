#include "minishell.h"

/*void	exec_pipe(t_input *input, int j, char **cmd1, char **cmd2)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
	char	*valid_access;

	if (pipe(pipe_fd) != 0)
		ft_printf("failed to create pipe");
	pid1 = fork();
	if (pid1 == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		input->cmds[j] = cmd1;
		valid_access = get_access_string(cmd1);
		execve(valid_access, cmd1, g_environ);
		free(valid_access);
		ft_printf("failed to exec first command\n");
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		input->cmds[j] = cmd2;
		valid_access = get_access_string(cmd2);
		execve(valid_access, cmd2, g_environ);
		if (exec_cmd(input, j))
			execve(valid_access, cmd2, g_environ);
		free(valid_access);
		ft_printf("failed to exec second command\n");
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);
}*/

int		spawn_proc (int in, int out, char **cmd)
{
	pid_t pid;

	if ((pid = fork ()) == 0)
	{
		if (in != 0)
		{
			dup2 (in, 0);
			close (in);
		}
		if (out != 1)
		{
			dup2 (out, 1);
			close (out);
		}
		return execvp(cmd[0], cmd);
	}
	return pid;
}

int		fork_pipes(int n, t_input *input, int j)
{
	int i;
	int in, fd [2];
	int index;
	char **cmd;
	
	in = 0;
	i = -1;
	int l = -1;
	int k;
	while (input->cmds[j][i])
	{
		index = 0;
		while (input->cmds[j][++l] && ft_strcmp(input->cmds[j][l], "|") == 0)
			index++;
		cmd = (char **)malloc(sizeof(char *) * index + 1);
		k = -1;
		while (ft_strcmp(input->cmds[j][++k], "|") == 0)
			cmd[i] = input->cmds[j][i];
		for (cmd[++k])
		{
			pipe (fd);
			spawn_proc (in, fd [1], cmd);
			close (fd [1]);
			in = fd [0];
		}
	if (in != 0)
		dup2 (in, 0);
	return execvp(cmd[0], cmd);
}

int check_for_pipe(t_input *input, int j)
{
	char *ls[] = {"ls", "-l", NULL};
	char *cat[] = {"cat", "-e", NULL};
	char *awk[] = {"awk", "{printf $1}", NULL};
	char ***cmds;
	int	nbr_pipes;
	int	i;

	/*ft_printf("%s   %s\n", input->cmds[0][0], input->cmds[0][1]);
	while (input->cmds[j] && input->cmds[j][++i])
	{
		if (ft_strcmp(input->cmds[j][i], "|") == 0)
			nbr_pipes++;
	}
	cmds = (char ***)malloc(sizeof(char **) * (nbr_pipes + 1));
	nbd_pipes = -1;
	int fix = 0;
	while (input->cmds[j] && input->cmds[j][++i])
	{
		fix = i;
		while ((pipe_index = ft_strchr(input->cmds[i][
			
		if (ft_strcmp(input->cmds[j][i], "|") == 0)
		{
			//move_elements_in_array(input->cmds[j], i);
			cmds[++nbr_pipes] = (char ***)malloc(sizeof(char **) * (pipe_index + 2));
			while (++i < pipe_index)
				cmds[nbr_pipes][fix++] = input->cmds[j][i];

	}
	*/
	//char **cmd[] = {ls, cat, awk, NULL};
	fork_pipes(3, input);
	return (1);
}
/*
int	check_for_pipe(t_input *input, int j)
{
	int		i;
	int		pipe_index;
	char	**cmd1;
	char	**cmd2;

	pipe_index = -1;
	i = -1;
	while (input->cmds[j] && input->cmds[j][++i])
	{
		if (ft_strchr(input->cmds[j][i], '|'))
		{
			pipe_index = i;
			break;
		}
	}
	if (pipe_index == -1)
		return (0);
	move_elements_in_array(input->cmds[j], pipe_index);
	i = -1;
	cmd1 = (char **)malloc(sizeoyyf(char *) * (pipe_index + 2));
	while (++i < pipe_index)
		cmd1[i] = input->cmds[j][i];
	cmd1[i] = NULL;
	cmd2 = &input->cmds[j][pipe_index];
	exec_pipe(input, j, cmd1, cmd2);
	free(cmd1);
	return (1);
}*/
