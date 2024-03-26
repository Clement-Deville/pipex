/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:27:54 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/26 11:27:25 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	set_input(char *filename, t_command *first_command)
{
	int	fd;

	if (access(filename, R_OK) != 0)
	{
		first_command->pid = NO_FORK;
		first_command->status = 1;
		return (perror(filename), 0);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			first_command->pid = NO_FORK;
			first_command->status = 1;
			return (perror(filename), 0);
		}
		return (perror("Open"), -1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("Dup2 error"), -1);
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (fd);
}

int	set_output(char *filename, t_command *last_command)
{
	int	fd;

	if (access(filename, W_OK) != 0 && errno != ENOENT)
	{
		last_command->pid = NO_FORK;
		last_command->status = 1;
		return (perror(filename), 0);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			last_command->pid = NO_FORK;
			last_command->status = 1;
			return (perror(filename), 0);
		}
		return (perror("Open"), -1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), -1);
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (fd);
}

int	set_output_append(char *filename, t_command *last_command)
{
	int	fd;

	if (access(filename, W_OK) != 0 && errno != ENOENT)
	{
		last_command->pid = NO_FORK;
		last_command->status = 1;
		return (perror(filename), 0);
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			last_command->pid = NO_FORK;
			last_command->status = 1;
			return (perror(filename), 0);
		}
		return (perror("Open"), -1);
	}
	if (do_dup2(fd, STDOUT_FILENO) == -1)
		return (-1);
	if (do_close(fd) == -1)
		return (-1);
	return (fd);
}
