/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_outfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:42:47 by gino              #+#    #+#             */
/*   Updated: 2024/09/02 17:09:57 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui free une liste d'outfiles*/
void	free_outfiles(t_outfile **outfiles)
{
	t_outfile	*current;
	t_outfile	*next;

	current = *outfiles;
	if (!current)
		return ;
	while (current != NULL)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		free(current);
		current = next;
	}
	*outfiles = NULL;
}

/*Fonction qui cree un nouvelle outfile*/
static t_outfile	*new_outfile(char *name, int type)
{
	t_outfile	*outfile;
	char		*str;

	outfile = malloc(sizeof(t_outfile));
	if (!outfile)
		return (NULL);
	str = ft_strdup(name);
	if (!str)
		return (free(outfile), NULL);
	outfile->name = str;
	outfile->append = false;
	if (type == APPEND)
		outfile->append = true;
	outfile->next = NULL;
	return (outfile);
}

/*Ajout d'un outfile a la liste*/
static void	add_outfile(t_outfile **outfiles, t_outfile *new)
{
	t_outfile	*lst;

	if (*outfiles == NULL)
		*outfiles = new;
	else
	{
		lst = *outfiles;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new;
	}
}

/*Fonction qui cree une liste d'outfiles*/
t_outfile	*create_outfiles_list(t_token *current)
{
	t_outfile	*outfiles;
	t_outfile	*new;

	outfiles = NULL;
	new = NULL;
	while (current)
	{
		if ((current->type == RT || current->type == APPEND)
			&& current->flag_error == FALSE)
		{
			if (current->next && current->next->value
				&& ft_isop(current->next->value) == FALSE)
				new = new_outfile(current->next->value, current->type);
			if (!new)
				return (free_outfiles(&outfiles), NULL);
			current->refered_flag = TRUE;
			current->next->refered_flag = TRUE;
			current->next->outfile_flag = TRUE;
			add_outfile(&outfiles, new);
			current = current->next;
		}
		else
			current = current->next;
	}
	return (outfiles);
}
