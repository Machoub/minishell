/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gino <gino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:03:28 by gino              #+#    #+#             */
/*   Updated: 2024/08/08 20:28:53 by gino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui renvoie le nom des heredocs*/
static char	*get_name(int i)
{
	char	*nbr;
	char	*name;
	char	*tmp;

	nbr = NULL;
	name = NULL;
	nbr = ft_itoa(i);
	name = ft_strjoin(".tmp_hd", nbr);
	if (!name)
		return (NULL);
	if (!(access(name, F_OK)))
	{
		free(name);
		tmp = ft_strjoin(nbr, "_");
		if (!tmp)
			return (free(nbr), NULL);
		name = ft_strjoin(".tmp_hd", tmp);
		if (!name)
			return (free(tmp), free(nbr), NULL);
		free(tmp);
	}
	if (nbr)
		free(nbr);
	return (name);
}

/*Fonction qui cree les noms des heredocs et les renvoie dans un tableau*/
char	**create_hd_names(int nbr)
{
	char	**names;
	int		i;

	names = malloc(sizeof(char *) * (nbr + 1));
	if (!names)
		return (NULL);
	i = 0;
	while (i < nbr)
	{
		names[i] = get_name(i);
		i++;
	}
	names[i] = NULL;
	return (names);
}
