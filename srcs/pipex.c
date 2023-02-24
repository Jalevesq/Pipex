/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 08:27:29 by jalevesq          #+#    #+#             */
/*   Updated: 2023/02/24 18:00:45 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


// Check that there are 4 arguments and that each command contains something.
static void	checkargs(int ac, char **av, t_data *data)
{
	if (ac != 5)
		ft_putstr_error("Not good amount of argument (!=4)", 0, data);
	if (ft_strlen(av[2]) == 0 || ft_strlen(av[3]) == 0
		|| ft_strncmp(av[2], " ", 1) == 0 || ft_strncmp(av[3], " ", 1) == 0)
	{
		ft_putstr_error("Bad command.", 0, data);
	}
}

// Initialize variables in structure
void	ft_init(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->envp = envp;
	data->argv = argv;
}

// Main function. Opens and verifies file descriptors,
// find the path of the commands in envp and enter the ft_fork function.
void	ft_process(t_data *data)
{
	data->outfile = open(data->argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	data->infile = open(data->argv[1], O_RDONLY, 0777);
	if (data->infile < 0)
		ft_putstr_error("Bad Input file.\n", 0, data);
	find_path(data);
	ft_fork(data);
	ft_2d_free(data->path);
	exit(0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	checkargs(argc, argv, &data);
	ft_init(&data, argc, argv, envp);
	ft_process(&data);
	return (0);
}
