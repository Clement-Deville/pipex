/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:27:54 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/21 15:40:29 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// int	set_input(char *filename)
// {
// 	int	fd;

// 	if (access(filename, R_OK) != 0)
// 	{
// 		perror(filename);
// 		filename = ft_strdup("/dev/null");
// 		if (filename == NULL)
// 			return (perror("Malloc error"), -1);
// 	}
// 	fd = open(filename, O_RDONLY);
// 	if (fd == -1)
// 		perror("Open error");
// 	if (ft_strncmp(filename, "/dev/null", 11) == 0)
// 		free(filename);
// 	if (fd == -1)
// 		return (-1);
// 	if (dup2(fd, STDIN_FILENO) == -1)
// 		return (perror("Dup2 error"), -1);
// 	if (close(fd) == -1)
// 		return (perror("Close error"), -1);
// 	return (fd);
// }

int	set_input(char *filename)
{
	int	fd;

	if (access(filename, R_OK) != 0)
		return (perror(filename), -1);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Open error"), -1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("Dup2 error"), -1);
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (fd);
}

int	set_output(char *filename)
{
	int	fd;

	if (access(filename, W_OK) != 0 && errno != ENOENT)
		return (perror(filename), -1);
	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
		return (perror("Open error"), -1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), -1);
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (fd);
}

// int	set_output(char *filename)
// {
// 	int	fd;

// 	if (access(filename, W_OK) != 0 && errno == EACCES)
// 	{
// 		perror(filename);
// 		filename = ft_strdup("/dev/null");
// 		if (filename == NULL)
// 			return (perror("Malloc error"), -1);
// 	}
// 	fd = open(filename, O_WRONLY | O_CREAT, 0777);
// 	if (fd == -1)
// 		perror("Open error");
// 	if (ft_strncmp(filename, "/dev/null", 11) == 0)
// 		free(filename);
// 	if (fd == -1)
// 		return (-1);
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 		return (perror("Dup2 error"), -1);
// 	if (close(fd) == -1)
// 		return (perror("Close error"), -1);
// 	return (fd);
// }
