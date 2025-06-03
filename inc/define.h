/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:01:45 by machouba          #+#    #+#             */
/*   Updated: 2024/07/30 15:05:32 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include "../libft/inc/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>

# define MINICHILL "minichill>"

# define FALSE 0
# define TRUE 1
# define SKIP 2

# define SUCCESS 1
# define FAIL -1

# define DOUBLE_QUOTES '\"'
# define SINGLE_QUOTE '\''

# define HEREDOC 1
# define APPEND 2
# define PIPE 3
# define LT 4
# define RT 5
# define WORD 6
# define NEWLINE_ERROR 7
# define QUOTES_ERROR 8
# define SINGLE_QUOTE_ERROR 9
# define DOUBLE_QUOTE_ERROR 10
# define QWORD 11
# define DOUBLE_PIPE_ERROR 12
# define LIM 13
# define PIPE_AT_END 14
# define HDEXEC 15

# define MAXFDS 1024

#endif