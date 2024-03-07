/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:09:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/07 11:42:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define IN 0
# define OUT 1

# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# include <fcntl.h>

void	check_inout(char *const argv[]);
int		*open_inout(char *const argv[]);

void	check_access(const char *filename);
int		exec_cmd(const char *path, char *const args[]);
int		do_unlink(const char *pathname);
int		do_pipe(int pipfd[2]);
int		do_dup2(int oldfd, int newfd);

#endif
