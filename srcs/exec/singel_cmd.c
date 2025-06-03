/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singel_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gino <gino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:32:07 by machouba          #+#    #+#             */
/*   Updated: 2024/08/02 17:37:03 by gino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	parent_handler(t_data *data, t_redirect *redirection,
		t_command *command)
{
	int	fd_input_backup;
	int	fd_output_backup;

	fd_input_backup = dup(STDIN_FILENO);
	fd_output_backup = dup(STDOUT_FILENO);
	dup2(redirection->input_fd, STDIN_FILENO);
	dup2(redirection->output_fd, STDOUT_FILENO);
	if (redirection->input_fd != STDIN_FILENO)
		close(redirection->input_fd);
	if (redirection->output_fd != STDOUT_FILENO)
		close(redirection->output_fd);
	free(redirection);
	if (ft_strcmp(command->args_lst->value, "exit") == 0)
	{
		dup2(fd_input_backup, STDIN_FILENO);
		dup2(fd_output_backup, STDOUT_FILENO);
		close(fd_input_backup);
		close(fd_output_backup);
	}
	data->exit_return = excec_builtin(data, command);
	dup2(fd_input_backup, STDIN_FILENO);
	dup2(fd_output_backup, STDOUT_FILENO);
	close(fd_input_backup);
	close(fd_output_backup);
}

void	exec_one_cmd(t_data *data)
{
	t_command	*command;
	t_redirect	*redirect;
	int			xit;

	command = data->commands;
	if (!command)
		return ;
	redirect = redir(data, command);
	if (!redirect)
	{
		xit = data->exit_return;
		free_all(data);
		free(redirect);
		exit(xit);
	}
	dup2(redirect->input_fd, STDIN_FILENO);
	dup2(redirect->output_fd, STDOUT_FILENO);
	if (redirect->input_fd != STDIN_FILENO)
		close(redirect->input_fd);
	if (redirect->output_fd != STDOUT_FILENO)
		close(redirect->output_fd);
	free(redirect);
	execve_cmd(data, command);
}

int	exec_sing_cmd(t_data *data)
{
	t_command	*cmd;
	t_redirect	*redirection;

	cmd = data->commands;
	if (cmd == NULL || cmd->args_lst == NULL)
		return (data->exit_return);
	redirection = redir(data, cmd);
	if (redirection == NULL)
	{
		reinit_data(data);
		return (data->exit_return);
	}
	if (redirection->input_fd == -1)
		return (1);
	if (redirection->output_fd == -1)
	{
		if (redirection->input_fd != STDIN_FILENO)
			close(redirection->input_fd);
		return (1);
	}
	parent_handler(data, redirection, cmd);
	return (data->exit_return);
}
