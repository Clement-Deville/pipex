/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 13:09:42 by cdeville          #+#    #+#             */
/*   Updated: 2024/03/19 12:00:54 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0
# define WRITE 1

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define NO_FORK -2

# define DONOT_EXIST 127
# define CANT_EXEC 126

# include <stdio.h>
# include <unistd.h>
# include <libft.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>

int		check_access(const char *filename);
int		exec_cmd(const char *path, char *const args[], char *const envp[]);
int		do_unlink(const char *pathname);
int		do_pipe(int pipfd[2]);
int		do_dup2(int oldfd, int newfd);

t_bool	are_in_child_one(int pid1);
t_bool	are_in_child_two(int pid1, int pid2);

void	free_commands(char ***cmds);
char	***parse_commands(int argc, char **argv);

// UTILS

void	print_commands(char ***cmds);

#endif
