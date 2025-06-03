/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:03:23 by gino              #+#    #+#             */
/*   Updated: 2024/09/04 14:22:21 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui recupere la taille de la liste des envs*/
int	envs_lst_size(t_env *env)
{
	int		i;
	t_env	*current;

	i = 0;
	current = env;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}

/*Fonction qui recupere la taille de la liste des args*/
int	args_lst_len(t_arg *args)
{
	int	i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}

/*Fonction qui check si il faut append, besoin pour redir.c*/
int	append_check(t_command	*cmd, char *name)
{
	t_outfile	*current;

	current = cmd->outfiles;
	while (current)
	{
		if (!(ft_strcmp(current->name, name)))
		{
			if (current->append == TRUE)
				return (TRUE);
			else
				return (FALSE);
		}
		current = current->next;
	}
	return (-1);
}

/*Fonction qui affiche exit puis qui exit vraiment*/
void	exit_display(t_data *data, int status)
{
	ft_putstr_fd("exit\n", 1);
	free_all(data);
	exit(status);
}
