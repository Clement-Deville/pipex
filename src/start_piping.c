/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_piping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 11:24:06 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/25 18:43:08 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// int	start_piping(char ***cmds, char *envp[])
// {
// 	int	i;
// 	int	*pipefd;
// 	int	*pid_tab;
// 	int	status;
// 	int	access_status;

// 	i = 0;
// 	pid_tab = (int *)malloc(sizeof(int) * nbr_of_cmds(cmds));
// 	if (pid_tab == NULL)
// 		return (perror("Error de malloc"), 7);
// 	pipefd = (int *)malloc(sizeof(int) * (2 * nbr_of_cmds(cmds)));
// 	if (pipefd == NULL)
// 	{
// 		free(pid_tab);
// 		return (perror("Error de malloc"), 7);
// 	}
// 	while (cmds[i] && cmds[i + 1])
// 	{
// 		if (pipe(&pipefd[2 * i]) == -1)
// 		{
// 			free(pid_tab);
// 			free(pipefd);
// 			return (perror("Pipe error"), -2);
// 		}
// 		access_status = check_access(cmds[i][0]);
// 		if (access_status == 0)
// 		{
// 			pid_tab[i] = fork();
// 			if (pid_tab[i] < 0)
// 			{
// 				free(pid_tab);
// 				free(pipefd);
// 				return (perror("Fork error"), -3);
// 			}
// 			if (are_in_child_one(pid_tab[i]))
// 			{
// 				if (i > 0)
// 					connect_read(&pipefd[2 * i]);
// 				connect_write(&pipefd[2 * i]);
// 				close_useless_fd(pipefd, i);
// 				exit (exec_cmd(cmds[i][0], cmds[i], envp));
// 			}
// 		}
// 		else
// 			pid_tab[i] = NO_FORK;
// 		i++;
// 	}
// 	access_status = check_access(cmds[i][0]);
// 	if (access_status == 0)
// 	{
// 		pid_tab[i] = fork();
// 		if (pid_tab[i] < 0)
// 		{
// 			free(pid_tab);
// 			free(pipefd);
// 			return (perror("Fork error"), -3);
// 		}
// 		if (are_in_child_one(pid_tab[i]))
// 		{
// 			if (i > 0)
// 				connect_read(&pipefd[2 * i]);
// 			close_useless_fd(pipefd, i);
// 			exit (exec_cmd(cmds[i][0], cmds[i], envp));
// 		}
// 	}
// 	else
// 		pid_tab[i] = NO_FORK;
// 	close_parent(pipefd, i);
// 	status = wait_for_all(pid_tab, i, access_status);
// 	if (status == -1)
// 	{
// 		free(pid_tab);
// 		free(pipefd);
// 		return (perror("Wait error"), -4);
// 	}
// 	free(pid_tab);
// 	free(pipefd);
// 	return (status);
// }

static int	allocate(int **pipefd, int nbr_of_cmds)
{
	*pipefd = (int *)malloc(sizeof(int) * (2 * nbr_of_cmds));
	if (pipefd == NULL)
		return (perror("Error de malloc"), -1);
	return (0);
}

// static int	allocate(int **pipefd, int **pid_tab, int nbr_of_cmds)
// {
// 	*pid_tab = (int *)malloc(sizeof(int) * nbr_of_cmds);
// 	if (pid_tab == NULL)
// 		return (perror("Error de malloc"), -1);
// 	*pipefd = (int *)malloc(sizeof(int) * (2 * nbr_of_cmds));
// 	if (pipefd == NULL)
// 	{
// 		free(pid_tab);
// 		return (perror("Error de malloc"), -1);
// 	}
// 	return (0);
// }

int	do_fork(t_command *cmds, int i, int *pipefd, char *envp[])
{
	cmds[i].pid = fork();
	if (cmds[i].pid < 0)
		return (free(pipefd), perror("Fork error"), 1);
	if (are_in_child_one(cmds[i].pid))
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

int	start_piping(t_command *cmds, char *envp[])
{
	int	i;
	int	*pipefd;
	int	status;
	int	access_status;

	i = 0;
	if (allocate(&pipefd, nbr_of_cmds(cmds)) != 0)
		return (1);
	while (cmds[i].args)
	{
		if (cmds[i + 1].args != NULL && pipe(&pipefd[2 * i]) == -1)
			return (free(pipefd), perror("Pipe error"), 1);
		access_status = check_command_access(cmds[i].args[0]);
		if (access_status == 0 && cmds[i].pid != NO_FORK)
		{
			if (do_fork(cmds, i, pipefd, envp) == 1)
				return (free(pipefd), free_commands(cmds), 1);
		}
		else
			cmds[i].pid = NO_FORK;
		i++;
	}
	i--;
	close_parent(pipefd, i);
	status = wait_for_all(cmds, i, access_status);
	free(pipefd);
	return (status);
}

// int	start_piping(char ***cmds, char *envp[])
// {
// 	int	i;
// 	int	*pipefd;
// 	int	*pid_tab;
// 	int	status;
// 	int	access_status;

// 	i = 0;
// 	if (allocate(&pipefd, &pid_tab, nbr_of_cmds(cmds)) != 0)
// 		return (-1);
// 	while (cmds[i])
// 	{
// 		if (cmds[i + 1] && pipe(&pipefd[2 * i]) == -1)
// 		{
// 			ft_free("%p%p", pid_tab, pipefd);
// 			return (perror("Pipe error"), -2);
// 		}
// 		access_status = check_command_access(cmds[i][0]);
// 		if (access_status == 0)
// 		{
// 			pid_tab[i] = fork();
// 			if (pid_tab[i] < 0)
// 			{
// 				ft_free("%p%p", pid_tab, pipefd);
// 				return (perror("Fork error"), -3);
// 			}
// 			if (are_in_child_one(pid_tab[i]))
// 			{
// 				if (i > 0)
// 					connect_read(&pipefd[2 * i]);
// 				if (cmds[i + 1])
// 					connect_write(&pipefd[2 * i]);
// 				close_useless_fd(pipefd, i);
// 				exit (exec_cmd(cmds[i][0], cmds[i], envp));
// 			}
// 		}
// 		else
// 			pid_tab[i] = NO_FORK;
// 		i++;
// 	}
// 	i--;
// 	close_parent(pipefd, i);
// 	status = wait_for_all(pid_tab, i, access_status);
// 	ft_free("%p%p", pid_tab, pipefd);
// 	if (status == -1)
// 		return (perror("Wait error"), -4);
// 	return (status);
// }
