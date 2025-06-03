/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:12:38 by gino              #+#    #+#             */
/*   Updated: 2024/07/29 15:47:39 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui ferme et free les pipes*/
static void	free_pipes(int **pipes, int idx)
{
	while (idx > 0)
	{
		close(pipes[idx][0]);
		close(pipes[idx][1]);
		if (pipes[idx])
			free(pipes[idx]);
		idx--;
	}
	free(pipes);
}

/*Fonction qui ferme juste les pipes ?*/
void	close_pipes(t_data *data)
{
	int	i;

	i = 0;
	if (!data->pipe_ends)
		return ;
	while (i < data->cmd_nbr - 1)
	{
		close(data->pipe_ends[i][0]);
		close(data->pipe_ends[i][1]);
		i++;
	}
}

/*Fonction qui cree les fd des pipes je crois*/
int	**create_pipes_fd(int nbr)
{
	int	**tab;
	int	i;

	i = 0;
	tab = malloc(sizeof(int *) * nbr);
	if (!tab)
		return (perror("minichill: "), NULL);
	while (i < nbr)
	{
		tab[i] = malloc(sizeof(int) * 2);
		if (!tab[i] || pipe(tab[i]) == -1)
		{
			free_pipes(tab, i);
			return (perror("minichill: "), NULL);
		}
		i++;
	}
	return (tab);
}
