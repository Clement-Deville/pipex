/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:41:24 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/29 14:59:40 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	*get_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

int	check_command_access(const char *path)
{
	if (access(path, R_OK) == 0)
		if (access(path, X_OK) == 0)
			return (0);
	// perror(path);
	if (errno == EACCES)
		return (CANT_EXEC);
	if (errno == ENOENT)
		return (DONOT_EXIST);
	else
		return (128);
}

char	**add_dir(char **split_path)
{
	int		i;
	char	*temp;

	i = 0;
	while (split_path[i])
	{
		temp = split_path[i];
		split_path[i] = ft_strjoin(split_path[i], "/");
		if (split_path[i] == NULL)
		{
			split_path[i] = temp;
			ft_free("%s", split_path);
			return (NULL);
		}
		free(temp);
		i++;
	}
	return (split_path);
}

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

char	**add_cmd_to_path(char **split_path, const char *cmd)
{
	int		i;
	char	**complete_path;

	i = 0;
	complete_path = (char **)malloc(sizeof(char *) * (len(split_path) + 1));
	if (complete_path == NULL)
		return (perror("Malloc error"), NULL);
	complete_path[len(split_path)] = NULL;
	while (split_path[i])
	{
		complete_path[i] = ft_strjoin(split_path[i], cmd);
		if (complete_path[i] == NULL)
			return (ft_free("%s", complete_path), NULL);
		i++;
	}
	return (complete_path);
}

void	print_not_found(char *cmd)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("\n", 2);
}

int	change_path(char **cmd, char *new_path)
{
	char	*temp;

	temp = *cmd;
	*cmd = ft_strdup(new_path);
	if (*cmd == NULL)
	{
		*cmd = temp;
		return (perror("Malloc error"), -1);
	}
	return (free(temp), 0);
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

t_bool	is_path(char *path)
{
	if (path != NULL)
		if (path[0] == '.' || path[0] == '/')
			return (TRUE);
	return (FALSE);
}

int	check_for_path_access(char **cmd, char **paths)
{
	char	**complete_paths;
	int		access_status;

	if (is_path(*cmd) == TRUE)
		return (check_command_access(*cmd));
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

char	**parse_path(char *envp[])
{
	char		**split_path;
	char		*cut;
	const char	*path;

	path = get_path(envp);
	cut = ft_strchr(path, '/');
	split_path = ft_split(cut, ':');
	if (split_path == NULL)
		return (perror("Malloc error"), NULL);
	split_path = add_dir(split_path);
	return (split_path);
}

// int	check_for_path_access(char **cmd, char **envp)
// {
// 	char		**split_path;
// 	char		*cut;
// 	const char	*path;
// 	int			access_status;

// 	path = get_path(envp);
// 	cut = ft_strchr(path, '/');
// 	split_path = ft_split(cut, ':');
// 	if (split_path == NULL)
// 		return (free(cut), perror("Malloc error"), -1);
// 	split_path = add_dir(split_path);
// 	if (split_path == NULL)
// 		return (0);
// 	split_path = add_cmd_to_path(split_path, *cmd);
// 	if (split_path == NULL)
// 		return (0);
// 	access_status = check_for_all(split_path, cmd);
// 	ft_free("%s", split_path);
// 	return (access_status);
// }

int	exec_cmd(const char *path, char *const args[], char *envp[])
{
	if (execve(path, args, envp) == -1)
	{
		perror("Probleme a l'execution de la commande");
		return (1);
	}
	return (0);
}

void	free_commands(t_command *cmds)
{
	int	i;

	i = 0;
	while (cmds[i].args)
	{
		ft_free("%s", cmds[i].args);
		i++;
	}
	free(cmds);
}
