/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:36:02 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/26 19:08:11 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

t_bool	are_in_child(int pid1)
{
	if (pid1 == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	is_cmd_executable(t_command cmds)
{
	if (cmds.status == 0 && cmds.pid != NO_FORK)
		return (TRUE);
	else
		return (FALSE);
}

int	nbr_of_cmds(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].args)
	{
		i++;
	}
	return (i);
}
