/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:18:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/21 13:12:02 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>


void	connect_read(int *pipefd)
{
	close((pipefd - 2)[WRITE]);
	dup2((pipefd - 2)[READ], STDIN_FILENO);
	close((pipefd - 2)[READ]);
}

void	connect_write(int *pipefd)
{
	close(pipefd[READ]);
	dup2(pipefd[WRITE], STDOUT_FILENO);
	close(pipefd[WRITE]);
}

void	close_useless_fd(int *pipefd, int size)
{
	int	i;

	i = 0;
	if (size == 0)
		return ;
	while (i < size - 1)
	{
		close((pipefd + (2 * i))[READ]);
		close((pipefd + (2 * i))[WRITE]);
		i++;
	}
	return ;
}

int	close_parent(int *pipefd, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		close((pipefd + (2 * i))[READ]);
		close((pipefd + (2 * i))[WRITE]);
		i++;
	}
	return (0);
}
