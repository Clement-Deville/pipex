/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:27:54 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/22 17:14:12 by cdeville         ###   ########.fr       */
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
			return (perror("Open"), 0);
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
	fd = open(filename, O_WRONLY | O_CREAT, 0777);
	if (fd == -1)
	{
		if (errno == EACCES)
		{
			last_command->pid = NO_FORK;
			last_command->status = 1;
			return (perror("Open"), 0);
		}
		return (perror("Open"), -1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (perror("Dup2 error"), -1);
	if (close(fd) == -1)
		return (perror("Close error"), -1);
	return (fd);
}

int	set_input_here_doc(char *limiter)
{
	int		pid;
	char	*line;
	int		pipefd[2];

	(void)limiter;
	if (pipe(pipefd) == -1)
		return (perror("Error pipe"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("Error fork"), -1);
	if (pid == 0)
	{
		close(pipefd[READ]);
		while (1)
		{
			write(1, "here_doc>", 10);
			line = get_next_line(STDIN_FILENO);
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, pipefd[WRITE]);
			free(line);
		}
		exit (0);
	}
	if (pid > 0)
	{
		wait(NULL);
		close(pipefd[WRITE]);
		dup2(pipefd[READ], STDIN_FILENO);
		close(pipefd[READ]);
	}
	return (0);
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
			return (perror("Open"), 0);
		}
		return (perror("Open"), -1);
	}
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
