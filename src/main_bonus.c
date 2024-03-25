/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:03:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/25 14:10:53 by cdeville         ###   ########.fr       */
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
		cmds[i].status = 0;
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
	t_bool		here_doc;

	if (argc < 5)
		return (0);
	if (ft_strncmp("here_doc", argv[1], 10) == 0)
	{
		here_doc = TRUE;
		if (set_input_here_doc(argv[2]) == -1)
			return (1);
		cmds = parse(argc - 4, &argv[3]);
		if (cmds == NULL)
			return (1);
		if (set_output_append(argv[argc - 1],
				&cmds[nbr_of_cmds(cmds) - 1]) == -1)
			return (free_commands(cmds), 1);
	}
	else
	{
		cmds = parse(argc - 3, &argv[2]);
		if (cmds == NULL)
			return (1);
		if (set_input(argv[1], cmds) == -1
			|| set_output(argv[argc - 1], &cmds[nbr_of_cmds(cmds) - 1]) == -1)
			return (free_commands(cmds), 1);
	}
	status = start_piping(cmds, envp);
	free_commands(cmds);
	return (status);
}
