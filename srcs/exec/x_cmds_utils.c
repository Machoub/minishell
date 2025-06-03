/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_cmds_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:40:15 by machouba          #+#    #+#             */
/*   Updated: 2024/07/29 15:48:10 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	close_unused_pipes(t_data *data, t_redirect *redir)
{
	if (redir->input_fd != STDIN_FILENO)
		close(redir->input_fd);
	if (redir->output_fd != STDOUT_FILENO)
		close(redir->output_fd);
	close_pipes(data);
}

void	exit_null(t_data *data, t_redirect *redir)
{
	int	status;

	if (redir == NULL)
	{
		status = data->exit_return;
		free_all(data);
		exit(status);
	}
	return ;
}
