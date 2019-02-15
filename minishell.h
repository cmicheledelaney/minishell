/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:36:03 by ccodiga           #+#    #+#             */
/*   Updated: 2019/02/14 19:08:41 by ccodiga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _MINISHELL_H
# define _MINISHELL_H

# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <dirent.h>
# include <string.h>
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <time.h>
# include <grp.h>
# include <stdio.h>
# include "libft/libft.h"
# define RED "\033[31m"
# define BLU "\033[34m"
# define MAG "\033[1m\033[35m"
# define MAG2 "\033[0m\033[35m"
# define CYA "\033[1m\033[36m"
# define CYA2 "\033[0m\033[36m"
# define WHI "\033[0m\033[37m"
# define GRE  "\x1B[32m"
# define RESET "\033[0m\033[0m"
# define IS_EXPANSION(x) (x == '~' || x == '$')
# define QUOTES -1
# define DOUBLEQUOTES -2
# define IS_OPERATOR(x) (x == '|' || x == '>' || x == '<')

typedef struct	s_input
{
	char		*input_string;
	char		**cmds_strings;
	char		***cmds;
}				t_input;

char	**g_environ;
pid_t	g_pid_parent;
pid_t	g_pid_child;

int		ft_cd(t_input *input, int j);
int		ft_exit(t_input *input, int j);
int		ft_setenv(t_input *input, int j);
int		ft_env(t_input *input, int j);
int		ft_echo(t_input *input, int j);
int		ft_unsetenv(t_input *input, int j);
void	change_key(char *variable, char *key);
char	*get_key(char **dict, char *variable);
void	dollar_expansion(char **args);
void	get_args(t_input *input);
void	check_unescaped(t_input *input);
void	move_elements_in_array(char **array, int index);
int		exec_builtin(t_input *input, int j);
int		check_for_pipe(t_input *input, int j);
void	exec_pipe(t_input *input, int j, char **cmd1, char **cmd2);
int		is_in_between(char *input, int index, char embrace);
char	*convert_quotes(char *input, char quotes, char other, char conversion_value);
void	expansions(t_input *input, int i);
int		nbr_unquoted_char(char *string, char c);
void	check_for_openquotes(t_input  *input);
int		openquote_index(char *input, char c);
int		find_index_of_next_unembraced_seperator(char *string, char seperator);
int		fork_execve(char **cmd);
char	*get_access_string(char **cmd);
int		redirect(t_input *input, int j, char **cmd);

#endif
