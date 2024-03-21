/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:03:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/21 18:39:15 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

// int	main(int argc, char *argv[], char *envp[])
// {
// 	char	***cmds;
// 	int		status;

// 	if (argc < 5)
// 		return (0);
// 	cmds = parse_commands(argc - 3, &argv[2]);
// 	set_input(argv[1]);
// 	set_output(argv[argc - 1]);
// 	if (cmds == NULL)
// 		return (1);
// 	// print_commands(cmds);
// 	status = start_piping(cmds, envp);
// 	free_commands(cmds);
// 	return (status);
// }

void	init(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].args)
	{
		cmds[i].pid = 0;
		i++;
	}
}

t_command	*parse(int argc, char **argv)
{
	t_command	*cmds;
	int			i;

	i = 0;
	cmds = (t_command *)malloc(sizeof(t_command) * (argc + 1));
	if (cmds == NULL)
		return (NULL);
	cmds[argc].args = NULL;
	while (i < argc)
	{
		cmds[i].args = ft_split(argv[i], ' ');
		if (cmds[i].args == NULL)
		{
			while (i)
			{
				i--;
				ft_free("%s", cmds[i].args);
			}
			free(cmds);
			return (NULL);
		}
		i++;
	}
	init(cmds);
	return (cmds);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmds;
	int			status;

	if (argc < 5)
		return (0);
	// cmds = parse_commands(argc - 3, &argv[2]);
	cmds = parse(argc - 3, &argv[2]);
	set_input(argv[1], cmds);
	set_output(argv[argc - 1], &cmds[argc - 3]);
	if (cmds == NULL)
		return (1);
	// print_commands(cmds);
	status = start_piping(cmds, envp);
	free_commands(cmds);
	return (status);
}
