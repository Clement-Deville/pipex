/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:26:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/08 19:24:06 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char *argv[])
{
	int		fd[2];
	char	**cmd_one;
	char	**cmd_two;
	int		pid1;
	int		pid2;

	if (argc != 3)
		return (1);
	cmd_one = ft_split(argv[1], ' ');
	if (cmd_one == NULL)
		return (2);
	cmd_two = ft_split(argv[2], ' ');
	if (cmd_two == NULL)
	{
		free(cmd_one);
		return (3);
	}
	if (pipe(fd) == -1)
	{
		perror("Error when calling pipe");
		return (4);
	}
	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Error when calling fork1");
		return (5);
	}
	if (pid1 == 0)
	{
		close(fd[READ]);
		dup2(STDOUT_FILENO, fd[WRITE]);
		close(fd[WRITE]);
		if (execv(cmd_one[0], cmd_one) == -1)
		{
			perror("Probleme lors de l'execution de la commande 1");
			return (6);
		}
	}
	write(1, "Child one not done\n", 20);
	if (waitpid(pid1, NULL, 0) == -1)
	{
		perror("Error lors de waitpid sur enfant 1");
		return (7);
	}
	if (pid1 > 0)
	{
		pid2 = fork();
		if (pid1 == -1)
		{
			perror("Error when calling fork2");
			return (8);
		}
	}
	if (pid1 > 0 && pid2 == 0)
	{
		close(fd[WRITE]);
		dup2(STDIN_FILENO, fd[READ]);
		close(fd[READ]);
		if (execv(cmd_two[0], cmd_two) == -1)
		{
			perror("Probleme lors de l'execution de la commande 2");
			if (ft_free("%s %s", cmd_one, cmd_two) != 0)
			{
				perror("Error lors du free des arguments");
				return (14);
			}
			return (9);
		}
	}
	if (close(fd[READ]) == -1)
	{
		perror("Error when closing pipe form father");
		return (10);
	}
	if (close(fd[WRITE]) == -1)
	{
		perror("Error when closing pipe form father");
		return (11);
	}
	write(1, "Child one done\n", 16);
	if (waitpid(pid2, NULL, 0) == -1)
	{
		perror("Error lors de waitpid sur enfant 2");
		if (ft_free("%s %s", cmd_one, cmd_two) != 0)
		{
			perror("Error lors du free des arguments");
			return (14);
		}
		return (13);
	}
	write(1, "Child two done\n", 16);
	if (ft_free("%s %s", cmd_one, cmd_two) != 0)
	{
		perror("Error lors du free des arguments");
		return (14);
	}
	return (0);
}
