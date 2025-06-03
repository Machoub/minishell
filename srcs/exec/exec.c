/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gino <gino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:32:07 by machouba          #+#    #+#             */
/*   Updated: 2024/08/08 20:29:27 by gino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*exec de commands apres chaque pipes*/

int	execve_cmd(t_data *data, t_command *command)
{
	char	**envp;

	if (!command->args_lst || !command->args_lst->value)
		return (1);
	command->path = get_path_command(data, command->args_lst->value);
	if (ft_strcmp(command->args_lst->value, ".") == 0
		|| ft_strcmp(command->args_lst->value, "..") == 0)
		special_check(data, command->args_lst->value);
	ft_check_errors(data, command);
	if (access(command->path, X_OK) == -1)
	{
		ft_putstr_fd("minichill: ", 2);
		ft_putstr_fd(command->args_lst->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_all(data);
		exit(126);
	}
	envp = create_environment(data);
	execve(command->path, command->args, envp);
	free_env(envp);
	ft_putstr_fd("minichill: ", 2);
	perror(command->path);
	free_all(data);
	exit(126);
}

/*fork le process pour exec cmd*/

int	make_fork(t_data *data)
{
	int	i;

	data->ids = malloc(sizeof(int) * data->cmd_nbr);
	if (!data->ids)
		return (1);
	i = 0;
	while (i < data->cmd_nbr)
	{
		data->ids[i] = fork();
		if (data->ids[i] == -1)
			return (perror("minichill :"), -1);
		if (data->ids[i] == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (data->cmd_nbr == 1)
				exec_one_cmd(data);
			else
				handle_child_process(data, i);
			free_all(data);
			exit(0);
		}
		i++;
	}
	return (close_pipes(data), SUCCESS);
}

void	execute(t_data *data)
{
	signal(SIGINT, handler_dprompt);
	signal(SIGQUIT, handler_dprompt);
	if (data->cmd_nbr <= 0)
		return ;
	if (launch_hd(data) == -1)
		return ;
	if (data->cmd_nbr == 1 && is_builtin(data->commands) == TRUE)
		data->exit_return = exec_sing_cmd(data);
	else if (data->cmd_nbr == 1 && is_builtin(data->commands) == FALSE)
		make_fork(data);
	else if (data->cmd_nbr > 1)
	{
		data->pipe_ends = create_pipes_fd(data->cmd_nbr - 1);
		if (!data->pipe_ends)
			return ;
		make_fork(data);
	}
}
