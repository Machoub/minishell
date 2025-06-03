/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:01:38 by machouba          #+#    #+#             */
/*   Updated: 2024/09/04 14:19:17 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signum;

static void	exit_statu(t_data *data)
{
	if (g_signum != 0)
	{
		data->exit_return = g_signum + 128;
		g_signum = 0;
	}
}

static void	wait_childs(t_data *data)
{
	int	status;
	int	i;
	int	pid;

	if (!data->ids)
		exit_statu(data);
	else
	{
		status = 0;
		i = 0;
		while (i < data->cmd_nbr)
		{
			pid = wait(&status);
			if (pid == data->ids[data->cmd_nbr - 1])
			{
				data->exit_return = 0;
				if (WIFEXITED(status))
					data->exit_return = WEXITSTATUS(status);
				if (WIFSIGNALED(status))
					data->exit_return = WTERMSIG(status) + 128;
			}
			g_signum = 0;
			i++;
		}
	}
}

static void	ft_handler_signal(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = signum;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data *const	data = ft_init_data(argc, argv, envp);
	int				i;

	if (!data || argc != 1)
		return (-1);
	while (1)
	{
		signal(SIGINT, &ft_handler_signal);
		signal(SIGQUIT, SIG_IGN);
		data->input = readline(MINICHILL);
		if (!data->input)
			break ;
		exit_statu(data);
		if (data->input[0] != '\0')
			add_history(data->input);
		if (lexing(data) == SUCCESS && parse_command(data) == SUCCESS)
			execute(data);
		wait_childs(data);
		reinit_data(data);
	}
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("exit\n", 0);
	return (i = data->exit_return, rl_clear_history(), free_all(data), i);
}
