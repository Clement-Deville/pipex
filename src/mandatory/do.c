/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:44:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/26 19:09:43 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	do_pipe(int pipfd[2])
{
	if (pipe(pipfd) == -1)
	{
		perror("Erreur lors de la creatin du pipe");
		return (1);
	}
	return (0);
}

int	do_close(int fd)
{
	if (close(fd) == -1)
	{
		perror("Close error");
		return (-1);
	}
	return (0);
}

int	do_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("Erreur lors de dup2");
		return (1);
	}
	return (0);
}

int	do_fork(t_command *cmds, int i, int *pipefd, char *envp[])
{
	cmds[i].pid = fork();
	if (cmds[i].pid < 0)
		return (free(pipefd), perror("Fork error"), 1);
	if (are_in_child(cmds[i].pid))
	{
		if (i > 0)
			if (connect_read(&pipefd[2 * i]) == 1)
				return (1);
		if (cmds[i + 1].args)
			if (connect_write(&pipefd[2 * i]) == 1)
				return (1);
		if (close_useless_fd(pipefd, i) == 1)
			return (1);
		exit (exec_cmd(cmds[i].args[0], cmds[i].args, envp));
	}
	return (0);
}
