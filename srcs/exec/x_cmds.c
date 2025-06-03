/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_cmds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gino <gino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:40:18 by machouba          #+#    #+#             */
/*   Updated: 2024/08/30 11:33:22 by gino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Fonction pour exécuter la première commande dans un pipeline
static void	execute_first_command(t_data *data, t_command *command)
{
	t_redirect	*redir_info;
	int			exit_status;

	redir_info = redir(data, command);
	exit_null(data, redir_info);
	dup2(redir_info->input_fd, STDIN_FILENO);
	if (redir_info->output_fd == STDOUT_FILENO)
	{
		if (dup2(data->pipe_ends[0][1], STDOUT_FILENO) == -1)
			perror(NULL);
	}
	else
		dup2(redir_info->output_fd, STDOUT_FILENO);
	close_unused_pipes(data, redir_info);
	if (is_builtin(command) == 1)
	{
		exit_status = excec_builtin(data, command);
		free_all(data);
		free(redir_info);
		exit(exit_status);
	}
	free(redir_info);
	execve_cmd(data, command);
}

// Fonction pour exécuter une commande intermédiaire dans un pipeline

static void	execute_middle_command(t_data *data, t_command *command,
		int process_idx)
{
	t_redirect	*redir_info;
	int			exit_status;

	redir_info = redir(data, command);
	exit_null(data, redir_info);
	if (redir_info->input_fd == STDIN_FILENO)
		dup2(data->pipe_ends[process_idx - 1][0], STDIN_FILENO);
	else
		dup2(redir_info->input_fd, STDIN_FILENO);
	if (redir_info->output_fd == STDOUT_FILENO)
		dup2(data->pipe_ends[process_idx][1], STDOUT_FILENO);
	else
		dup2(redir_info->output_fd, STDOUT_FILENO);
	close_unused_pipes(data, redir_info);
	if (is_builtin(command) == 1)
	{
		exit_status = excec_builtin(data, command);
		free_all(data);
		free(redir_info);
		exit(exit_status);
	}
	free(redir_info);
	execve_cmd(data, command);
}

// Fonction pour exécuter la dernière commande dans un pipeline

static void	execute_last_command(t_data *data, t_command *command,
		int process_idx)
{
	t_redirect	*redir_info;
	int			exit_status;

	close(data->pipe_ends[process_idx - 1][1]);
	redir_info = redir(data, command);
	exit_null(data, redir_info);
	if (redir_info->input_fd == STDIN_FILENO)
		dup2(data->pipe_ends[process_idx - 1][0], STDIN_FILENO);
	else
		dup2(redir_info->input_fd, STDIN_FILENO);
	dup2(redir_info->output_fd, STDOUT_FILENO);
	close_unused_pipes(data, redir_info);
	if (is_builtin(command) == 1)
	{
		exit_status = excec_builtin(data, command);
		free_all(data);
		free(redir_info);
		exit(exit_status);
	}
	free(redir_info);
	execve_cmd(data, command);
}

// Fonction pour gérer les processus enfants dans le pipeline

void	handle_child_process(t_data *data, int process_idx)
{
	t_command	*current_command;

	current_command = data->commands;
	while (current_command && process_idx > current_command->pos)
		current_command = current_command->next;
	if (current_command == NULL || current_command->args_lst == NULL)
		return ;
	if (process_idx == 0)
		execute_first_command(data, current_command);
	else if (process_idx == data->cmd_nbr - 1)
		execute_last_command(data, current_command, process_idx);
	else
		execute_middle_command(data, current_command, process_idx);
}
