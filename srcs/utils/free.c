/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:00:12 by machouba          #+#    #+#             */
/*   Updated: 2024/07/30 19:51:16 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_hd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_heredoc)
	{
		if (data->names_heredoc && data->names_heredoc[i])
		{
			free(data->names_heredoc[i]);
			data->names_heredoc[i] = NULL;
		}
		i++;
	}
	if (data->names_heredoc)
		free(data->names_heredoc);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	data->names_heredoc = NULL;
	data->fd_heredoc = NULL;
}

static void	deslink(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->names_heredoc)
		return ;
	while (i < data->nbr_heredoc && data->names_heredoc[i])
	{
		if (data->names_heredoc[i])
			unlink(data->names_heredoc[i]);
		i++;
	}
}

static void	free_pipe_last(t_data *data)
{
	int	i;

	i = 0;
	if (data->pipe_ends)
	{
		close_pipes(data);
		while (i < data->cmd_nbr - 1)
		{
			if (data->pipe_ends[i])
				free(data->pipe_ends[i]);
			i++;
		}
		free(data->pipe_ends);
		data->pipe_ends = NULL;
	}
}

void	reinit_data(t_data *data)
{
	if (!data)
		return ;
	deslink(data);
	free_hd(data);
	if (data->tokens)
		free_token(&data->tokens);
	if (data->commands)
		free_commands_list(&data->commands);
	if (data->fd_heredoc)
		free(data->fd_heredoc);
	if (data->input)
		free(data->input);
	if (data->pipe_ends)
		free_pipe_last(data);
	if (data->ids)
		free(data->ids);
	data->nbr_heredoc = 0;
	data->cmd_nbr = 0;
	data->step = 0;
	data->input = NULL;
	data->fd_heredoc = NULL;
	data->ids = NULL;
}

void	free_all(t_data *data)
{
	if (!data)
		return ;
	reinit_data(data);
	if (data->envs)
		free_envs(&data->envs);
	if (data->exports)
		free_envs(&data->exports);
	free(data);
}
