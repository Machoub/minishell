/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:37:57 by machouba          #+#    #+#             */
/*   Updated: 2024/07/30 20:03:00 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui affiche un message passe en parametre*/
static void	display_msg(char *msg, int fd)
{
	ft_putstr_fd("minichill: ", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
}

/*Fonction qui verifie si option*/
static bool	check_option(char *str)
{
	if (!str || str[0] != '-')
		return (FALSE);
	if (!(ft_strcmp(str, "--")) || !(ft_strcmp(str, "-")))
		return (FALSE);
	if (!(ft_strncmp(str, "--", 2)) && str[2])
		return (TRUE);
	if (!(ft_strncmp(str, "-", 1)) && str[1])
		return (TRUE);
	return (FALSE);
}

/*Fonction builtin export*/
int	ft_export(t_data *data, t_command *cmd)
{
	t_arg	*args;
	int		status;

	status = 0;
	if (!data || !cmd || !cmd->args_lst || !cmd->args_lst->value)
		return (-1);
	args = cmd->args_lst;
	if (!args->next)
		return (print_exports(data), 0);
	args = args->next;
	if (!(ft_strcmp(args->value, "--")) && !args->next)
		return (print_exports(data), 0);
	if (!(ft_strcmp(args->value, "--")) && args->next)
		args = args->next;
	if (check_option(args->value))
		return (display_msg("export: Options are not authorized", 2), 2);
	while (args)
	{
		if (handle_input(data, args->value) == -1)
			status = 1;
		args = args->next;
	}
	return (status);
}
