/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 15:06:29 by machouba          #+#    #+#             */
/*   Updated: 2024/07/29 15:17:48 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	special_check(t_data *data, char *str)
{
	if (ft_strcmp(str, ".") == 0)
	{
		ft_putstr_fd("minichill: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": filename argument required\n", 2);
		free_all(data);
		exit(2);
	}
	if (ft_strcmp(str, "..") == 0)
	{
		ft_putstr_fd("minichill: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_all(data);
		exit(127);
	}
}
