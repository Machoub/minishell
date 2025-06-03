/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:37:49 by machouba          #+#    #+#             */
/*   Updated: 2024/09/04 16:12:13 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_case(t_arg *cur)
{
	if (ft_strbrk(cur->value, '!') == 1)
	{
		ft_putstr_fd("minichill: unset: '", 2);
		ft_putstr_fd(ft_strchr(cur->value, '!'), 2);
		ft_putstr_fd("': not valid\n", 2);
		return (1);
	}
	return (0);
}

int	ft_unset(t_data *data, t_arg *args)
{
	t_arg	*current;

	if (!data || !args || !args->value)
		return (FALSE);
	if (!(args->next))
		return (0);
	current = args->next;
	if (current && is_option(current->value))
	{
		ft_putstr_fd("minichill: unset: '", 2);
		ft_putstr_fd(current->value, 2);
		ft_putstr_fd("': not valid\n", 2);
		return (2);
	}
	if (check_case(current))
		return (2);
	while (current)
	{
		delete_env(&data->envs, current->value);
		remove_export(&data->exports, current->value);
		current = current->next;
	}
	return (0);
}
