/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalevesq <jalevesq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:09:21 by jalevesq          #+#    #+#             */
/*   Updated: 2023/02/24 17:55:24 by jalevesq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"


// Iterates through char **envp to find the line that contains PATH. Delete "PATH="
// from the beginning and then split at each ':' the path.
// Example of path:
// PATH=/Users/jalevesq/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin:/Users/jalevesq/homebrew/bin
void	find_path(t_data *data)
{
	int		i;
	char	*tmp;
	char	*trim;

	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp("PATH=", data->envp[i], 5) == 0)
		{
			trim = ft_strtrim(data->envp[i], "PATH=");
			data->path = ft_split(trim, ':');
			free(trim);
			i = 0;
			while (data->path[i])
			{
				tmp = ft_strjoin(data->path[i], "/");
				free(data->path[i]);
				data->path[i++] = tmp;
			}
			break ;
		}
		i++;
	}
}

// Try each combination of path partitions with the command in cmd[0] (The command passed as a parameter 
// to the program) until acces confirms that it is the right path

char	*cmd_path(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	if (ft_strncmp(data->cmd[0], "/", 1) == 0)
	{
		if (access(*data->cmd, X_OK) == 0)
			return (*data->cmd);
	}
	while (data->path[i])
	{
		tmp = ft_strjoin(data->path[i], data->cmd[0]);
		if (access(tmp, X_OK | F_OK) == 0)
			return (tmp);
		free(tmp);
		i++;
	}
	return (NULL);
}
