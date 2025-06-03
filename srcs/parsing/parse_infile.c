/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gino <gino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:42:45 by gino              #+#    #+#             */
/*   Updated: 2024/07/30 17:22:29 by gino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui free une liste d'infiles*/
void	free_infiles(t_infile **infiles)
{
	t_infile	*tok;
	t_infile	*next;

	tok = *infiles;
	if (!tok)
		return ;
	while (tok != NULL)
	{
		next = tok->next;
		if (tok->name)
			free(tok->name);
		if (tok->delimiter)
			free(tok->delimiter);
		free(tok);
		tok = next;
	}
	*infiles = NULL;
}

/*Fonction qui cree un infile ou un heredoc*/
static t_infile	*new_infile(char *str, int type, t_data *data)
{
	t_infile	*new;

	new = malloc(sizeof(t_infile));
	if (!new)
		return (NULL);
	new->expand_flag = TRUE;
	new->heredoc_nbr = 0;
	if (type == LT)
	{
		new->name = ft_strdup(str);
		if (!new->name)
			new->name = NULL;
		new->delimiter = NULL;
	}
	else if (type == HEREDOC)
	{
		new->name = NULL;
		new->heredoc_nbr = data->pos_heredoc;
		data->pos_heredoc++;
		new->delimiter = ft_strdup(str);
		if (!new->delimiter)
			new->delimiter = NULL;
	}
	new->next = NULL;
	return (new);
}

/*Ajout d'un infile a la liste*/
static void	add_infile(t_infile **infile_lst, t_infile *new)
{
	t_infile	*lst;

	if (!(*infile_lst))
		*infile_lst = new;
	else
	{
		lst = *infile_lst;
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

/*Creation d'un infile*/
static t_infile	*create_infile(t_token *next, t_token *tok, t_data *data)
{
	t_infile	*ret;

	ret = new_infile(next->value, tok->type, data);
	if (!ret)
		return (NULL);
	next->refered_flag = TRUE;
	if (next->type == LIM && next->expand_flag == FALSE)
		ret->expand_flag = FALSE;
	if (next->type == WORD)
		next->infile_flag = TRUE;
	return (ret);
}

/*Creation d'une liste d'infile*/
t_infile	*create_infile_list(t_data *data, t_token *tok)
{
	t_infile	*ret;
	t_infile	*new;

	ret = NULL;
	new = NULL;
	while (tok)
	{
		if ((tok->type == LT || tok->type == HEREDOC)
			&& tok->flag_error == false)
		{
			if (tok->next && (tok->next->type == WORD || tok->next->type == LIM)
				&& tok->next->flag_error == false)
			{
				new = create_infile(tok->next, tok, data);
				if (!new)
					return (free_infiles(&ret), NULL);
			}
			tok->refered_flag = TRUE;
			add_infile(&ret, new);
		}
		if (tok->flag_error == TRUE)
			break ;
		tok = tok->next;
	}
	return (ret);
}
