/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 10:14:42 by gino              #+#    #+#             */
/*   Updated: 2024/08/30 14:54:03 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handler_dprompt(int signal)
{
	if (signal == SIGINT)
	{
		g_signum = signal;
		rl_on_new_line();
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", STDIN_FILENO);
	}
	if (signal == SIGQUIT)
	{
		g_signum = signal;
		ft_putstr_fd("Quit: (core dumped)\n", STDOUT_FILENO);
	}
}

t_data	*ft_init_data(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(data));
	data->input = NULL;
	data->tokens = NULL;
	data->commands = NULL;
	data->envs = creates_envs_list(envp);
	data->exports = create_export_list(envp);
	data->nbr_heredoc = 0;
	data->pos_heredoc = -1;
	data->fd_heredoc = NULL;
	data->names_heredoc = NULL;
	data->exit_return = 0;
	data->builtins_return = 0;
	data->path = NULL;
	data->cmd_nbr = 0;
	data->ids = NULL;
	data->pipe_ends = NULL;
	data->step = 0;
	return (data);
}
