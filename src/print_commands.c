/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 10:02:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/22 17:58:35 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	print_commands(t_command *cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i].args)
	{
		j = 0;
		while (cmds[i].args[j])
		{
			ft_printf("%s\n", cmds[i].args[j]);
			j++;
		}
		i++;
	}
}
