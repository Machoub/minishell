/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:32:07 by machouba          #+#    #+#             */
/*   Updated: 2024/09/04 15:14:22 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui cree la boucle pour ecrire dans le heredoc*/
static void	write_hd(t_data *data, int fd, char *delimiter, int exp_flag)
{
	char	*content;

	while (1)
	{
		content = readline("> ");
		if (!content)
		{
			ft_putstr_fd("warning : heredoc limited by EOF\n", 2);
			break ;
		}
		if (exp_flag == TRUE && ft_strchr(content, '$') && ft_strcmp(content,
				delimiter) != 0)
			content = expand_string(data, content);
		if (!(ft_strcmp(content, delimiter)))
			break ;
		else
		{
			content = ft_strsjoin(content, ft_strdup("\n"));
			write(fd, content, ft_strlen(content));
			free(content);
		}
	}
	free(content);
}

/*Fonction qui cree les heredoc, ecrit dedans, renvoie le nombre*/
static int	exec_hd(t_data *data, t_command *cmd, int *fd, int i)
{
	t_infile	*current;
	int			count;

	current = cmd->infiles;
	count = 0;
	while (current && (i + count) < data->nbr_heredoc)
	{
		if (current->delimiter)
		{
			fd[i + count] = open(data->names_heredoc[i + count],
					O_WRONLY | O_RDONLY | O_CREAT, 0644);
			if (fd[i + count] == -1 || fd[i + count] > MAXFDS)
				return (ft_print_err(HDEXEC), free_all(data), -1);
			write_hd(data, fd[i + count], current->delimiter,
				current->expand_flag);
			close(fd[i + count]);
			count++;
		}
		current = current->next;
	}
	return (count);
}
/*Fonnction qui cree autant de heredoc que necessaire*/

static int	ft_hd(t_data *data)
{
	t_command	*current;
	int			i;

	i = 0;
	current = data->commands;
	while (current && i < data->nbr_heredoc)
	{
		i += exec_hd(data, current, data->fd_heredoc, i);
		if (i == data->nbr_heredoc)
			return (SUCCESS);
		else
			current = current->next;
	}
	return (-1);
}

static int	exec_hds(t_data *data)
{
	data->nbr_heredoc = get_heredocs_nbr(data->commands);
	if (data->nbr_heredoc == 0)
		return (SUCCESS);
	data->fd_heredoc = malloc(sizeof(int) * data->nbr_heredoc);
	if (!(data->fd_heredoc))
		return (-1);
	data->names_heredoc = create_hd_names(data->nbr_heredoc);
	if (!(data->names_heredoc))
		return (-1);
	create_hd_files(data);
	ft_hd(data);
	return (SUCCESS);
}

int	launch_hd(t_data *data)
{
	if (exec_hds(data) == -1)
	{
		if (check_error_print(data->tokens) == FALSE)
			error_pipe_at_end(data->tokens);
		return (-1);
	}
	if (check_error_print(data->tokens) == TRUE)
		return (-1);
	if (error_pipe_at_end(data->tokens) == -1)
		return (-1);
	return (SUCCESS);
}
