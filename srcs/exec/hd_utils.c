/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 15:03:31 by gino              #+#    #+#             */
/*   Updated: 2024/09/04 14:53:56 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui retourne si erreur ou non, et qui affiche*/
int	check_error_print(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->flag_error == TRUE)
		{
			ft_print_err(current->type_error);
			return (TRUE);
		}
		current = current->next;
	}
	return (FALSE);
}

/*Fonction qui recupere le prochain infile*/
t_infile	*gni(t_infile *infile, char *name)
{
	t_infile	*current;

	current = infile;
	if (!current)
		return (NULL);
	while (current)
	{
		if (!(current->name) && !(ft_strcmp(current->delimiter, name)))
			return (current);
		current = current->next;
	}
	return (NULL);
}

/*J'ai pas compris ce qu'elle fait, ca renvoie le nombre d'infiles ?*/
static int	ft_inside(t_token *current, t_infile *infile, t_data *data,
		int count)
{
	t_infile	*new_inf;
	int			i;

	new_inf = infile;
	i = 0;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (current->next && current->next->type == LIM)
			{
				current->next->heredoc = ft_strdup(data->names_heredoc[count
						+ i]);
				new_inf = gni(infile, current->next->value);
				if (!new_inf)
					return (i);
				else
					new_inf->name = ft_strdup(data->names_heredoc[count + i]);
				new_inf = new_inf->next;
				i++;
			}
		}
		current = current->next;
	}
	return (i);
}

/*Fonction qui cree les fichiers pour les heredocs ?*/
void	create_hd_files(t_data *data)
{
	t_token		*tok_cur;
	t_command	*cmd_cur;
	t_infile	*infile;
	int			count;

	count = 0;
	cmd_cur = data->commands;
	if (!cmd_cur)
		return ;
	infile = cmd_cur->infiles;
	while (cmd_cur && count < data->nbr_heredoc)
	{
		tok_cur = cmd_cur->tokens;
		count += ft_inside(tok_cur, infile, data, count);
		cmd_cur = cmd_cur->next;
	}
}
