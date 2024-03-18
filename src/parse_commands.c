/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:09:06 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/18 10:09:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	***parse_commands(int argc, char **argv)
{
	char	***cmds;
	int		i;

	i = 0;
	cmds = (char ***)malloc(sizeof(char **) * (argc + 1));
	if (cmds == NULL)
		return (NULL);
	cmds[argc] = NULL;
	while (argv[i])
	{
		cmds[i] = ft_split(argv[i], ' ');
		if (cmds[i] == NULL)
		{
			while (i)
			{
				i--;
				ft_free("%s", cmds[i]);
			}
			return (NULL);
		}
		i++;
	}
	return (cmds);
}
