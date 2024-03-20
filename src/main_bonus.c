/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:03:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/20 16:53:14 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	wait_for_all(int *pid_tab, int size, int access_status)
{
	int	i;
	int	status;
	int	exit_value;

	i = 0;
	exit_value = 0;
	while (i <= size)
	{
		if (pid_tab[i] != NO_FORK && waitpid(pid_tab[i], &status, 0) == -1)
		{
			perror("Error lors du wait");
			return (-1);
		}
		if (pid_tab[i] != NO_FORK && WIFEXITED(status))
			exit_value = WEXITSTATUS(status);
		if (pid_tab[i] != NO_FORK && WIFSIGNALED(status))
			exit_value = 128 + WTERMSIG(status);
		i++;
	}
	if (access_status != 0)
		exit_value = access_status;
	return (exit_value);
}

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

int	nbr_of_cmds(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		i++;
	}
	return (i);
}

int	start_piping(char ***cmds, char *envp[])
{
	int	i;
	int	*pipefd;
	int	*pid_tab;
	int	status;
	int	access_status;

	i = 0;
	pid_tab = (int *)malloc(sizeof(int) * nbr_of_cmds(cmds));
	if (pid_tab == NULL)
		return (perror("Error de malloc"), 7);
	pipefd = (int *)malloc(sizeof(int) * (2 * nbr_of_cmds(cmds)));
	if (pipefd == NULL)
	{
		free(pid_tab);
		return (perror("Error de malloc"), 7);
	}
	while (cmds[i] && cmds[i + 1])
	{
		if (pipe(&pipefd[2 * i]) == -1)
		{
			free(pid_tab);
			free(pipefd);
			return (perror("Pipe error"), -2);
		}
		access_status = check_access(cmds[i][0]);
		if (access_status == 0)
		{
			pid_tab[i] = fork();
			if (pid_tab[i] < 0)
			{
				free(pid_tab);
				free(pipefd);
				return (perror("Fork error"), -3);
			}
			if (are_in_child_one(pid_tab[i]))
			{
				if (i > 0)
					connect_read(&pipefd[2 * i]);
				connect_write(&pipefd[2 * i]);
				close_useless_fd(pipefd, i);
				exit (exec_cmd(cmds[i][0], cmds[i], envp));
			}
		}
		else
			pid_tab[i] = NO_FORK;
		i++;
	}
	access_status = check_access(cmds[i][0]);
	if (access_status == 0)
	{
		pid_tab[i] = fork();
		if (pid_tab[i] < 0)
		{
			free(pid_tab);
			free(pipefd);
			return (perror("Fork error"), -3);
		}
		if (are_in_child_one(pid_tab[i]))
		{
			if (i > 0)
				connect_read(&pipefd[2 * i]);
			close_useless_fd(pipefd, i);
			exit (exec_cmd(cmds[i][0], cmds[i], envp));
		}
	}
	else
		pid_tab[i] = NO_FORK;
	close_parent(pipefd, i);
	status = wait_for_all(pid_tab, i, access_status);
	if (status == -1)
	{
		free(pid_tab);
		free(pipefd);
		return (perror("Wait error"), -4);
	}
	free(pid_tab);
	free(pipefd);
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	***cmds;
	int		status;

	if (argc < 5)
		return (0);
	cmds = parse_commands(argc - 3, &argv[2]);
	set_input(argv[1]);
	set_output(argv[argc - 1]);
	if (cmds == NULL)
		return (1);
	// print_commands(cmds);
	status = start_piping(cmds, envp);
	free_commands(cmds);
	return (status);
}
