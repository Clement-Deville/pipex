/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:22:10 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/25 18:41:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	wait_for_all(t_command *cmds, int size, int access_status)
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
		if (cmds[i].pid == NO_FORK && cmds[i].status == 1)
			exit_value = 1;
		i++;
	}
	if (access_status != 0 && exit_value != 1)
		exit_value = access_status;
	return (exit_value);
}

// int	wait_for_all(int *pid_tab, int size, int access_status)
// {
// 	int	i;
// 	int	status;
// 	int	exit_value;

// 	i = 0;
// 	exit_value = 0;
// 	while (i <= size)
// 	{
// 		if (pid_tab[i] != NO_FORK && waitpid(pid_tab[i], &status, 0) == -1)
// 		{
// 			perror("Error lors du wait");
// 			return (-1);
// 		}
// 		if (pid_tab[i] != NO_FORK && WIFEXITED(status))
// 			exit_value = WEXITSTATUS(status);
// 		if (pid_tab[i] != NO_FORK && WIFSIGNALED(status))
// 			exit_value = 128 + WTERMSIG(status);
// 		i++;
// 	}
// 	if (access_status != 0)
// 		exit_value = access_status;
// 	return (exit_value);
// }
