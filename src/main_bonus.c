/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:03:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/18 19:14:50 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	wait_for_all(int *pid_tab, int size)
{
	int	i;
	int	status;
	int	exit_value;

	i = 0;
	ft_printf("Size = %d\n", size + 1);
	while (i < size)
	{
		if (pid_tab[i] != NO_FORK && waitpid(pid_tab[i], &status, 0) == -1)
		{
			perror("Error lors du wait");
			return (-1);
		}
		if (WIFEXITED(status))
		{
			exit_value = WEXITSTATUS(status);
			ft_putnbr_fd(exit_value, STDERR_FILENO);
		}
		if (WIFSIGNALED(status))
		{
			ft_printf("Process %d terminated by signal %d\n", i, WTERMSIG(status));
		}
		i++;
	}
	if (pid_tab[i] != NO_FORK && waitpid(pid_tab[i], &status, 0) == -1)
	{
		perror("Error lors du wait");
		return (-1);
	}
	if (pid_tab[i] != NO_FORK && WIFEXITED(status))
	{
		exit_value = WEXITSTATUS(status);
		ft_putnbr_fd(exit_value, STDERR_FILENO);
	}
	if (pid_tab[i] != NO_FORK && WIFSIGNALED(status))
	{
		ft_printf("Process %d terminated by signal %d\n", i, WTERMSIG(status));
	}
	return (exit_value);
}

void	connect_read(int *pipefd)
{
	close(pipefd[WRITE]);
	dup2((pipefd - 1)[READ], STDIN_FILENO);
	close((pipefd - 1)[READ]);
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
		close((pipefd + i)[READ]);
		close((pipefd + i)[WRITE]);
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
		close(pipefd[READ]);
		close(pipefd[WRITE]);
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

	i = 0;
	pid_tab = (int *)malloc(sizeof(int) * nbr_of_cmds(cmds));
	if (pid_tab == NULL)
	{
		perror("Error de malloc");
		return (7);
	}
	pipefd = (int *)malloc(sizeof(int) * (2 * nbr_of_cmds(cmds)));
	if (pipefd == NULL)
	{
		perror("Erreur de malloc");
		free(pid_tab);
		return (8);
	}
	while (cmds[i] && cmds[i + 1])
	{
		//check access command
		//create pipe
		//fork and exec
		//set stdin as pipe[READ] in parent
		if (pipe(&pipefd[2 * i]) == -1)
		{
			perror("Pipe error");
			free(pid_tab);
			return (-2);
		}
		if (check_access(cmds[i][0]) == TRUE)
		{
			pid_tab[i] = fork();
			if (pid_tab[i] < 0)
			{
				perror("Fork error");
				free(pid_tab);
				return (-3);
			}
			if (are_in_child_one(pid_tab[i]))
			{
				if (i > 0)
					connect_read(&pipefd[2 * i]);
				connect_write(&pipefd[2 * i]);
				close_useless_fd(pipefd, i);
				return (exec_cmd(cmds[i][0], cmds[i], envp));
			}
		}
		else
			pid_tab[i] = NO_FORK;
		i++;
	}
	if (check_access(cmds[i][0]) == TRUE)
	{
		pid_tab[i] = fork();
		if (pid_tab[i] < 0)
		{
			perror("Fork error");
			free(pid_tab);
			return (-3);
		}
		if (are_in_child_one(pid_tab[i]))
		{
			if (i > 0)
				connect_read(&pipefd[2 * i]);
			close_useless_fd(pipefd, i);
			return (exec_cmd(cmds[i][0], cmds[i], envp));
		}
	}
	else
		pid_tab[i] = NO_FORK;
	close_parent(pipefd, i);
	status = wait_for_all(pid_tab, i);
	if (status == -1)
	{
		perror("Wait error");
		free(pid_tab);
		return (-4);
	}
	free(pid_tab);
	return (status);
	//wait for all processes to be done
}

int	main(int argc, char *argv[], char *envp[])
{
	char	***cmds;
	int		status;

	if (argc < 3)
		return (1);
	cmds = parse_commands(argc - 1, &argv[1]);
	if (cmds == NULL)
		return (1);
	// print_commands(cmds);
	status = start_piping(cmds, envp);
	free_commands(cmds);
	return (status);
}
