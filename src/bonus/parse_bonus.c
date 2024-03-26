/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 18:01:32 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/26 15:28:41 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

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

void	parse_here_doc(int argc, char *argv[], t_command **cmds)
{
	if (set_input_here_doc(argv[2]) == -1)
		exit (1);
	*cmds = parse(argc - 4, &argv[3]);
	if (*cmds == NULL)
		exit (1);
	if (set_output_append(argv[argc - 1],
			&(*cmds)[nbr_of_cmds(*cmds) - 1]) == -1)
	{
		free_commands(*cmds);
		exit (1);
	}
}

void	parse_standard(int argc, char *argv[], t_command **cmds)
{
	*cmds = parse(argc - 3, &argv[2]);
	if (*cmds == NULL)
		exit (1);
	if (set_input(argv[1], *cmds) == -1
		|| set_output(argv[argc - 1], &(*cmds)[nbr_of_cmds(*cmds) - 1]) == -1)
	{
		free_commands(*cmds);
		exit (1);
	}
}
