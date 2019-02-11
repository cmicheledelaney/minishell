#include "minishell.h"

void	exec_pipe(t_input *input, int j, char **cmd1, char **cmd2)
{
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pipe_fd) != 0)
		ft_printf("failed to create pipe");
	pid1 =fork();
	if (pid1 == 0)
	{
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		input->cmds[j] = cmd1;
		//run_commands(input->cmds[j]);
		execvp(cmd1[0], cmd1);
		ft_printf("failed to exec first command\n");
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(pipe_fd[0], 0);
		close(pipe_fd[1]);
		input->cmds[j] = cmd2;
		execvp(cmd2[0], cmd2);
		//if (exec_cmd(input, j))
		//	run_commands(input->cmds[j]);
		ft_printf("failed to exec second command\n");
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	wait(NULL);
	wait(NULL);
}

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
	cmd1 = (char **)malloc(sizeof(char *) * (pipe_index + 2));
	while (++i < pipe_index)
		cmd1[i] = input->cmds[j][i];
	cmd1[i] = NULL;
	cmd2 = &input->cmds[j][pipe_index];
	exec_pipe(input, j, cmd1, cmd2);
	free(cmd1);
	return (1);
}
