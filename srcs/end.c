/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 14:19:38 by jalevesq          #+#    #+#             */
/*   Updated: 2023/02/24 18:18:17 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Displays an error message 
// closes all fd's if the flag passed in parameter is equal to 1.

void	ft_putstr_error(char *str, int flag, t_data *data)
{
	if (flag == 1)
	{
		close_fd(data);
		ft_putstr_fd(str, 2);
	}
	else
		ft_putstr_fd(str, 2);
	exit(1);
}

// Free **char.
void	ft_2d_free(char **to_free)
{
	int	i;

	i = 0;
	while (to_free[i])
		free(to_free[i++]);
	free(to_free[i]);
	free(to_free);
}

// Closes all fd's.
void	close_fd(t_data *data)
{
	close(data->pipefd[0]);
	close(data->pipefd[1]);
	close(data->infile);
	close(data->outfile);
}
