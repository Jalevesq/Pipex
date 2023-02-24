/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 10:57:06 by jalevesq          #+#    #+#             */
/*   Updated: 2023/02/24 18:15:26 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


// Function that initializes the pipe,
// creates the child processes and waits for the children to finish 
void	ft_fork(t_data *data)
{
	if (pipe(data->pipefd) == -1)
		ft_putstr_error("Pipe Error\n", 0, data);
	data->pid1 = fork();
	if (data->pid1 == -1)
		ft_putstr_error("first fork pid == -1", 1, data);
	else if (data->pid1 == 0)
		ft_firstchild(data);
	data->pid2 = fork();
	if (data->pid2 == -1)
		ft_putstr_error("second fork pid == -1", 1, data);
	else if (data->pid2 == 0)
		ft_secondchild(data);
	close_fd(data);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
}


// First child process. Use ft_split to separate the first command from its parameter (e.g. ls -l),
// pass through the cmd_path function, change the fd of pipefd with stdout and then of infile with stdin
// (so that the input of the command that will be executed later is the infile and the output is stored
// in the pipe instead of stdout) and finish by executing the command.
void	ft_firstchild(t_data *data)
{
	data->cmd = ft_split(data->argv[2], ' ');
	data->path_command = cmd_path(data);
	if (!data->path_command)
	{
		ft_2d_free(data->cmd);
		ft_putstr_error(NO_PATH1, 1, data);
	}
	if (dup2(data->pipefd[1], STDOUT_FILENO) == -1)
		ft_putstr_error("First child dup2 error\n", 0, data);
	if (dup2(data->infile, STDIN_FILENO) == -1)
		ft_putstr_error("First child dup2 infile error\n", 0, data);
	close_fd(data);
	ft_2d_free(data->path);
	execve(data->path_command, data->cmd, data->envp);
	free(data->path_command);
	ft_2d_free(data->cmd);
	ft_putstr_error("Error first execve failed\n", 0, data);
}

// Second child process. Uses split and passes through the cmd_path function as in the first process.
// Then change the stdin to pipefd[0] and the stdout to the outfile (So that the input of the command is what 
// is in the pipe and the result is stored in the outfile). Finish by executing the command.

void	ft_secondchild(t_data *data)
{
	data->cmd = ft_split(data->argv[3], ' ');
	data->path_command = cmd_path(data);
	if (!data->path_command)
	{
		ft_2d_free(data->cmd);
		ft_putstr_error(NO_PATH2, 1, data);
		exit(1);
	}
	if (dup2(data->pipefd[0], STDIN_FILENO) == -1)
		ft_putstr_error("Dup2 of pipefd0 stdin failed.\n", 0, data);
	if (dup2(data->outfile, STDOUT_FILENO) == -1)
		ft_putstr_error("Dup2 of outfile stdout failed.\n", 0, data);
	close_fd(data);
	ft_2d_free(data->path);
	execve(data->path_command, data->cmd, data->envp);
	free(data->path_command);
	ft_2d_free(data->cmd);
	ft_putstr_error("Error: second execve failed\n", 0, data);
}
