/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 11:24:50 by gino              #+#    #+#             */
/*   Updated: 2024/08/30 17:50:56 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_builtin(t_command *cmd)
{
	char	*str;

	if (!cmd || !cmd->args_lst || !cmd->args_lst->value)
		return (FALSE);
	str = cmd->args_lst->value;
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0 || ft_strcmp(str, ":") == 0
		|| ft_strcmp(str, "!") == 0)
		return (TRUE);
	return (FALSE);
}

bool	is_option(char *cmd)
{
	if (!cmd || ft_strcmp(cmd, "--") == 0 || ft_strcmp(cmd, "-") == 0)
		return (FALSE);
	if (*cmd == '-' && *(cmd + 1) != '\0')
		return (TRUE);
	return (FALSE);
}

int	excec_builtin(t_data *data, t_command *cmd)
{
	if (!data || !cmd || !cmd->args_lst || !cmd->args_lst->value)
		return (1);
	if (ft_strlen(cmd->args_lst->value) == 0)
		return (1);
	if (ft_strcmp(cmd->args_lst->value, "pwd") == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp(cmd->args_lst->value, "env") == 0)
		return (ft_env(data));
	if (ft_strcmp(cmd->args_lst->value, "cd") == 0)
		return (ft_cd(data->envs, cmd));
	if (ft_strcmp(cmd->args_lst->value, "echo") == 0)
		return (ft_echo(data, cmd));
	if (ft_strcmp(cmd->args_lst->value, ":") == 0)
		return (0);
	if (ft_strcmp(cmd->args_lst->value, "!") == 0)
		return (1);
	if (ft_strcmp(cmd->args_lst->value, "export") == 0)
		return (ft_export(data, cmd));
	if (ft_strcmp(cmd->args_lst->value, "unset") == 0)
		return (ft_unset(data, cmd->args_lst));
	if (ft_strcmp(cmd->args_lst->value, "exit") == 0)
		return (ft_exit(data, cmd->args_lst));
	return (1);
}
