/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:03:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/29 18:10:37 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmds;
	char		**paths;
	int			status;

	if (argc < 5)
		return (ft_putstr_fd("Error, you need at least 4 arguments.\n", 2), 0);
	if (ft_strncmp("here_doc", argv[1], 10) == 0)
		parse_here_doc(argc, argv, &cmds);
	else
		parse_standard(argc, argv, &cmds);
	paths = parse_path(envp);
	if (paths == NULL)
		return (free_commands(cmds), 1);
	status = start_piping(cmds, envp, paths);
	free_commands(cmds);
	ft_free("%s", paths);
	return (status);
}
