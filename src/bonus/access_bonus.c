/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:58:57 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/29 17:59:52 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

int	check_command_access(const char *path)
{
	if (access(path, R_OK) == 0)
		if (access(path, X_OK) == 0)
			return (0);
	if (errno == EACCES)
		return (CANT_EXEC);
	if (errno == ENOENT)
		return (DONOT_EXIST);
	else
		return (128);
}

int	check_for_all(char **paths, char **cmd)
{
	int		i;
	int		access_status;
	char	*access_denied_path;

	i = 0;
	access_denied_path = NULL;
	while (paths[i])
	{
		access_status = check_command_access(paths[i]);
		if (access_status == 0)
			return (change_path(cmd, paths[i]));
		if (access_status == CANT_EXEC)
			access_denied_path = paths[i];
		i++;
	}
	if (access_denied_path)
	{
		access_status = check_command_access(access_denied_path);
		return (perror(access_denied_path), access_status);
	}
	if (access_status != 0)
		print_not_found(*cmd);
	return (access_status);
}

int	check_for_path_access(char **cmd, char **paths)
{
	char	**complete_paths;
	int		access_status;

	if (is_path(*cmd) == TRUE)
	{
		access_status = check_command_access(*cmd);
		if (access_status != 0)
			perror(*cmd);
		return (access_status);
	}
	else
	{
		complete_paths = add_cmd_to_path(paths, *cmd);
		if (complete_paths == NULL)
			return (-1);
		access_status = check_for_all(complete_paths, cmd);
		ft_free("%s", complete_paths);
		return (access_status);
	}
}
