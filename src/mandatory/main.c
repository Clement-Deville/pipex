/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:26:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/28 17:31:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmds;
	int			status;
	// char		*path;

	// path = get_path(envp);
	// ft_printf("%s\n", path);
	// check_for_path_access("cat", path);
	if (argc != 5)
		return (ft_putstr_fd("Error, you need 4 arguments.\n", 2), 0);
	parse_standard(argc, argv, &cmds);
	status = start_piping(cmds, envp);
	free_commands(cmds);
	return (status);
}
