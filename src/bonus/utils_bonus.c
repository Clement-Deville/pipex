/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:36:02 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/29 18:14:33 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	len(char **split)
{
	int	i;

	i = 0;
	if (split == NULL)
		return (0);
	while (split[i])
		i++;
	return (i);
}

t_bool	is_path(char *path)
{
	if (path != NULL)
		if (path[0] == '.' || path[0] == '/')
			return (TRUE);
	return (FALSE);
}

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
