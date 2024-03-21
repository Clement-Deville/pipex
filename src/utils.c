/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:36:02 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/21 11:17:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

t_bool	are_in_child_one(int pid1)
{
	if (pid1 == 0)
		return (TRUE);
	return (FALSE);
}

t_bool	are_in_child_two(int pid1, int pid2)
{
	if (pid1 > 0 && pid2 == 0)
		return (TRUE);
	return (FALSE);
}

int	nbr_of_cmds(char ***cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		i++;
	}
	return (i);
}
