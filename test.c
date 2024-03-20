/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:00 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/20 14:35:52 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char *argv[], char *envp[])
{
	int	fd;
	int	pid;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	dup2(fd, STDIN_FILENO);
	close(fd);
	pid = fork();
	if (pid > 0)
		execve(argv[1], &argv[1], envp);
	wait(NULL);
	return (0);
}
