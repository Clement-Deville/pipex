/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:03:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/21 16:38:54 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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
