/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:26:33 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/29 17:20:38 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmds;
	char		**paths;
	int			status;

	if (argc != 5)
		return (ft_putstr_fd("Error, you need 4 arguments.\n", 2), 0);
	parse_standard(argc, argv, &cmds);
	paths = parse_path(envp);
	if (paths == NULL)
		return (free_commands(cmds), 1);
	status = start_piping(cmds, envp, paths);
	free_commands(cmds);
	ft_free("%s", paths);
	return (status);
}
