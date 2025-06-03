/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:38:04 by machouba          #+#    #+#             */
/*   Updated: 2024/08/07 14:22:45 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui check si option -n*/
static int	check_if_n(char *str)
{
	while (*str && is_space(*str) == TRUE)
		str++;
	if (!str || *str != '-')
		return (FALSE);
	str++;
	while (*str && *str == 'n')
		str++;
	while (*str && is_space(*str) == TRUE)
		str++;
	if (*str == '\0')
		return (TRUE);
	return (FALSE);
}

/*Fonction qui determine si on doit afficher un \n ou pas*/
static int	check_nl(t_arg *arg)
{
	if (arg && arg->next && check_if_n(arg->next->value) == TRUE)
		return (FALSE);
	return (TRUE);
}

/*Fonction qui gere si -nnnnnn */
static t_arg	*handle_many_n(t_arg *arg)
{
	t_arg	*current;

	current = arg;
	while (current && check_if_n(current->value) == TRUE)
		current = current->next;
	return (current);
}

/*Fonction qui affiche la valeur de l'arg*/
static void	print_res(t_arg *arg)
{
	if (!(arg->value))
		ft_putstr_fd(" ", 1);
	else
		ft_putstr_fd(arg->value, 1);
	if (arg->next)
		ft_putstr_fd(" ", 1);
}

/*Fonction builtin echo*/
int	ft_echo(t_data *data, t_command *cmd)
{
	t_arg	*current;

	(void)data;
	current = cmd->args_lst;
	if (!current || !(current->value))
		return (-1);
	current = handle_many_n(current->next);
	while (current)
	{
		print_res(current);
		current = current->next;
	}
	if (check_nl(cmd->args_lst))
		ft_putstr_fd("\n", 1);
	return (0);
}
