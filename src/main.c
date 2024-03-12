/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:26:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/12 15:03:28 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// int	main(int argc, char *argv[])
// {
// 	int		fd[2];
// 	char	**cmd_one;
// 	char	**cmd_two;
// 	int		pid1;
// 	int		pid2;

// 	pid2 = -1;
// 	if (argc != 3)
// 		return (1);
// 	cmd_one = ft_split(argv[1], ' ');
// 	if (cmd_one == NULL)
// 		return (2);
// 	cmd_two = ft_split(argv[2], ' ');
// 	if (cmd_two == NULL)
// 	{
// 		free(cmd_one);
// 		return (3);
// 	}
// 	if (pipe(fd) == -1)
// 	{
// 		perror("Error when calling pipe");
// 		return (4);
// 	}
// 	pid1 = fork();
// 	if (pid1 < 0)
// 	{
// 		perror("Error when calling fork1");
// 		return (5);
// 	}
// 	if (are_in_child_one(pid1) == TRUE)
// 	{
// 		dup2(fd[READ], STDOUT_FILENO);
// 		close(fd[WRITE]);
// 		close(fd[READ]);
// 		exit(execv(cmd_one[0], cmd_one));
// 	}
// 	write(1, "Child one not done\n", 20);
// 	if (waitpid(pid1, NULL, 0) == -1)
// 	{
// 		perror("Error lors de waitpid sur enfant 1");
// 		return (7);
// 	}
// 	write(1, "Child one done\n", 16);
// 	if (are_in_child_one(pid1) == FALSE)
// 	{
// 		pid2 = fork();
// 		if (pid2 == -1)
// 		{
// 			perror("Error when calling fork2");
// 			return (8);
// 		}
// 	}
// 	if (are_in_child_two(pid1, pid2) == FALSE)
// 	{
// 		if (close(fd[READ]) == -1)
// 		{
// 			perror("Error when closing pipe form father");
// 			return (10);
// 		}
// 		if (close(fd[WRITE]) == -1)
// 		{
// 			perror("Error when closing pipe form father");
// 			return (11);
// 		}
// 	}
// 	if (are_in_child_two(pid1, pid2) == TRUE)
// 	{
// 		dup2(fd[WRITE], STDIN_FILENO);
// 		close(fd[READ]);
// 		close(fd[WRITE]);
// 		exit(execv(cmd_two[0], cmd_two));
// 	}
// 	if (waitpid(pid2, NULL, 0) == -1)
// 	{
// 		perror("Error lors de waitpid sur enfant 2");
// 		if (ft_free("%s %s", cmd_one, cmd_two) != 0)
// 		{
// 			perror("Error lors du free des arguments");
// 			return (14);
// 		}
// 		return (13);
// 	}
// 	write(1, "Child two done\n", 16);
// 	if (ft_free("%s %s", cmd_one, cmd_two) != 0)
// 	{
// 		perror("Error lors du free des arguments");
// 		return (14);
// 	}
// 	return (0);
// }

char	***parse_commands(int argc, char **argv)
{
	char	***cmds;
	char	**cmd_one;
	char	**cmd_two;

	(void)argc;
	cmd_one = ft_split(argv[1], ' ');
	if (cmd_one == NULL)
		return (NULL);
	cmd_two = ft_split(argv[2], ' ');
	if (cmd_two == NULL)
	{
		free(cmd_one);
		return (NULL);
	}
	cmds = (char ***)malloc(sizeof(char **) * 2);
	if (cmds == NULL)
	{
		ft_free("%s %s", cmds[0], cmds[1]);
		return (NULL);
	}
	cmds[0] = cmd_one;
	cmds[1] = cmd_two;
	return (cmds);
}

int	main(int argc, char *argv[])
{
	int		fd[2];
	char	***cmds;
	int		pid1;
	int		pid2;
	int		status1;
	int		status2;

	pid2 = -1;
	if (argc != 3)
		return (1);
	cmds = parse_commands(argc, argv);
	if (cmds == NULL)
		return (2);
	if (pipe(fd) == -1)
	{
		perror("pipex: error when calling pipe");
		return (4);
	}
	pid1 = fork();
	if (are_in_child_one(pid1))
	{
		close(fd[READ]);
		dup2(fd[WRITE], STDOUT_FILENO);
		close(fd[WRITE]);
		if (execv(cmds[0][0], cmds[0]) == -1)
		{
			perror("pipex: error when executing command one");
			return (5);
		}
		return (0);
	}
	else
	{
		pid2 = fork();
	}
	if (are_in_child_two(pid1, pid2))
	{
		close(fd[WRITE]);
		dup2(fd[READ], STDIN_FILENO);
		close(fd[READ]);
		if (execv(cmds[1][0], cmds[1]) == -1)
		{
			perror("pipex: error when executing command two");
			return (6);
		}
		return (0);
	}
	close(fd[READ]);
	close(fd[WRITE]);
	if (waitpid(pid1, &status1, 0) == -1)
	{
		perror("pipex: error when calling wait on child 1");
		return (15);
	}
	if (WIFEXITED(status1) == TRUE)
	{
		if (WEXITSTATUS(status1))
			ft_printf("Child one exited anormaly with exit code %d\n", WEXITSTATUS(status1));
	}
	else
	{
		ft_printf("Child one exited anormaly");
	}
	if (waitpid(pid2, &status2, 0) == -1)
	{
		perror("pipex: error when calling wait on child 2");
		return (17);
	}
	if (WIFEXITED(status2) == TRUE)
	{
		if (WEXITSTATUS(status2))
			ft_printf("Child two exited anormaly with exit code %d\n", WEXITSTATUS(status2));
	}
	else
	{
		ft_printf("Child two exited anormaly");
	}
	if (ft_free("%s %s %p", cmds[0], cmds[1], cmds) != 0)
	{
		perror("pipex: error lors du free des arguments");
		return (14);
	}
	return (WEXITSTATUS(status2));
}
