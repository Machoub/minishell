/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:39:18 by gino              #+#    #+#             */
/*   Updated: 2024/08/06 16:28:49 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_command *cmd)
{
	char	*current;
	t_arg	*arg;

	if (!cmd || !cmd->args_lst || !cmd->args_lst->value)
		return (1);
	arg = cmd->args_lst;
	if (arg->next && is_option(arg->next->value))
		return (ft_putstr_fd("minichill: pwd: Options not authorized\n", 2), 2);
	current = getcwd(NULL, 0);
	if (!current)
		return (ft_putstr_fd("minichill: ", 2), perror(arg->value), 1);
	ft_putstr_fd(current, 1);
	ft_putstr_fd("\n", 1);
	free(current);
	return (0);
}
