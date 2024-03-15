/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 18:03:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/15 18:27:06 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	***parse_commands(int argc, char **argv)
{
	char	***cmds;
	char	**actual_cmd;
	int		i;

	i = 0;
	cmds = (char ***)malloc(sizeof(char **) * argc + 1);
	if (cmds == NULL)
		return (NULL);
	cmds[argc] == NULL;
	while (argv[i])
	{
		cmds[i] = ft_split(argv[i], " ");
		if (cmds[i] == NULL)
		{
			while (i)
			{
				i--;
				ft_free("%s", cmds[i]);
			}
		}
		i++;
	}
	return (cmds);
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc < 3)
		return (1);

}
