/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_piping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:24:06 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/26 16:49:35 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

static int	allocate(int **pipefd, int nbr_of_cmds)
{
	*pipefd = (int *)malloc(sizeof(int) * (2 * nbr_of_cmds));
	if (pipefd == NULL)
		return (perror("Error de malloc"), -1);
	return (0);
}

int	wait_for_all(t_command *cmds, int size)
{
	int	i;
	int	exit_value;

	i = 0;
	exit_value = 0;
	while (i <= size)
	{
		if (cmds[i].pid != NO_FORK
			&& waitpid(cmds[i].pid, &cmds[i].status, 0) == 1)
			return (perror("Wait error"), 1);
		if (cmds[i].pid != NO_FORK && WIFEXITED(cmds[i].status))
			exit_value = WEXITSTATUS(cmds[i].status);
		if (cmds[i].pid != NO_FORK && WIFSIGNALED(cmds[i].status))
			exit_value = 128 + WTERMSIG(cmds[i].status);
		if (cmds[i].pid == NO_FORK)
			exit_value = cmds[i].status;
		i++;
	}
	return (exit_value);
}

int	start_piping(t_command *cmds, char *envp[])
{
	int	i;
	int	*pipefd;

	i = 0;
	if (allocate(&pipefd, nbr_of_cmds(cmds)) != 0)
		return (1);
	while (cmds[i].args)
	{
		if (cmds[i + 1].args != NULL && pipe(&pipefd[2 * i]) == -1)
			return (free(pipefd), perror("Pipe error"), 1);
		if (cmds[i].status == 0)
			cmds[i].status = check_command_access(cmds[i].args[0]);
		if (is_cmd_executable(cmds[i]))
		{
			if (do_fork(cmds, i, pipefd, envp) == 1)
				return (free(pipefd), free_commands(cmds), 1);
		}
		else
			cmds[i].pid = NO_FORK;
		i++;
	}
	if (close_parent(pipefd, --i) == 1)
		return (1);
	return (wait_for_all(cmds, i));
}
