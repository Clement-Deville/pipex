/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:26:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/07 12:02:17 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char *argv[])
{
	int		pid_left;
	int		pid_right;
	int		*inout;

	if (argc != 5)
		return (1);
	check_inout(argv);
	inout = open_inout(argv);
	pid_left = fork();
	if (pid_left == -1)
	{
		perror("Erreur lors du fork");
		return (EXIT_FAILURE);
	}
	if (pid_left > 0)
	{
		pid_right = fork();
		if (pid_right == -1)
		{
			perror("Erreur lors du fork");
			return (EXIT_FAILURE);
		}
	}
	if (pid_left == 0)
	{
		ft_printf("Bonjour du fils gauche!\n");
		close (inout[IN]);
		close (inout[OUT]);
		return (0);
	}
	if (pid_left > 0 && pid_right > 0)
	{
		ft_printf("Bonjour du pere!\n");
		close (inout[IN]);
		close (inout[OUT]);
		return (0);
	}
	if (pid_right == -1)
	{
		perror("Erreur lors du fork");
		return (EXIT_FAILURE);
	}
	if (pid_right == 0)
	{
		ft_printf("Bonjour du fils droit!\n");
		// write(2, "Error", 6);
		close (inout[IN]);
		close (inout[OUT]);
		return (0);
	}
	return (0);
}
