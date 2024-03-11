/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:09:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/11 10:41:32 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0
# define WRITE 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# include <fcntl.h>
# include <sys/wait.h>

int		check_access(const char *filename);
int		exec_cmd(const char *path, char *const args[]);
int		do_unlink(const char *pathname);
int		do_pipe(int pipfd[2]);
int		do_dup2(int oldfd, int newfd);

t_bool	are_in_child_one(int pid1);
t_bool	are_in_child_two(int pid1, int pid2);

#endif
