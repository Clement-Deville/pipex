/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:26:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/07 17:51:48 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char *argv[])
{
	int		inout[2];

	(void)argc;
	check_access(argv[1]);
	inout[IN] = open(argv[1], O_RDONLY);
	if (inout[IN] == -1)
		perror("Erreur lors du call d'open");
	do_dup2(0, 4);
	close(0);
	do_dup2(inout[IN], 0);
	exec_cmd("/bin/cat", argv);
	return (0);
}
