/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:27:19 by jalevesq          #+#    #+#             */
/*   Updated: 2023/02/22 15:02:58 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <errno.h>

# define NO_PATH1 "Did not find path to first command.\n"
# define NO_PATH2 "Did not find path to second command.\n"

typedef struct s_data
{
	char	**envp;
	char	**argv;
	int		argc;
	char	**cmd;
	char	**path;
	char	*path_command;
	int		outfile;
	int		infile;
	pid_t	pid1;
	pid_t	pid2;
	int		pipefd[2];
}	t_data;

void	terminate(t_data *data);
void	ft_putstr_error(char *str, int flag, t_data *data);
void	ft_fork(t_data *data);
void	ft_firstchild(t_data *data);
void	ft_secondchild(t_data *data);
void	ft_2d_free(char **to_free);
void	find_path(t_data *data);
char	*cmd_path(t_data *data);
void	close_fd(t_data *data);

#endif