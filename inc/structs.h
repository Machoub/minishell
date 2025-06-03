/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:27:01 by gino              #+#    #+#             */
/*   Updated: 2024/09/04 15:29:49 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_infile
{
	char			*name;
	char			*delimiter;
	int				heredoc_nbr;
	int				expand_flag;
	struct s_infile	*next;
}					t_infile;

typedef struct s_outfile
{
	char				*name;
	bool				append;
	struct s_outfile	*next;

}					t_outfile;

typedef struct s_redirect
{
	char	*infile;
	char	*outfile;
	int		input_fd;
	int		output_fd;
}					t_redirect;

typedef struct s_arg
{
	char			*value;
	int				token_type;
	struct s_arg	*next;
}					t_arg;

typedef struct s_token /*Liste chainee tokens*/
{
	int				type;
	int				type_error;
	int				pos;
	int				flag_error;
	int				infile_flag;
	int				outfile_flag;
	bool			expand_flag;
	int				pipe_flag;
	int				refered_flag;
	char			*value;
	char			*heredoc;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*value;
	char			*key;
	char			*name;
	struct s_env	*next;
}					t_env;

typedef struct s_command
{
	t_infile			*infiles;
	t_outfile			*outfiles;
	t_arg				*args_lst;
	t_token				*tokens;
	char				**args;
	char				*input;
	char				*path;
	int					pos;
	struct s_command	*next;
}					t_command;

typedef struct s_data
{
	char		*input;
	t_token		*tokens;
	t_command	*commands;
	t_env		*envs;
	t_env		*exports;
	int			nbr_heredoc;
	int			pos_heredoc;
	int			*fd_heredoc;
	char		**names_heredoc;
	int			exit_return;
	int			builtins_return;
	char		*path;
	int			cmd_nbr;
	int			*ids;
	int			**pipe_ends;
	int			step;
}					t_data;

#endif