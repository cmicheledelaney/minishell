/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccodiga <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 13:36:03 by ccodiga           #+#    #+#             */
/*   Updated: 2019/01/17 16:47:03 by ccodiga          ###   ########.fr       */
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

typedef struct	s_input
{
	char		*input;
	char		**cmds_strings;
	char		***cmds_tokens;
}				t_input;

char	**g_environ;
char	*g_input;
pid_t	g_pid_parent;
pid_t	g_pid_child;

int		ft_cd(char **args);
int		ft_exit(char **args);
int		ft_setenv(char **args);
int		ft_env(char **args);
int		ft_echo(char **args);
int		ft_unsetenv(char **args);
void	change_key(char *variable, char *key);
char	*get_key(char **dict, char *variable);
void	dollar_extension(char **args);
char	***get_args(void);
void	check_unescaped(void);

#endif
