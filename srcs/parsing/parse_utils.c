/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:42:49 by gino              #+#    #+#             */
/*   Updated: 2024/09/04 12:24:07 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	double_free(t_token *token, char *input)
{
	if (input)
		free(input);
	if (token)
		free_token(&token);
}

/*Fonction pour extraire un token*/
t_token	*get_token(t_token *token)
{
	t_token	*new;
	t_token	*ret;
	char	*str;

	ret = NULL;
	while (token != NULL && token->type != PIPE)
	{
		str = NULL;
		if (token->value)
		{
			str = ft_strdup(token->value);
			if (!str)
				return (free_token(&ret), NULL);
		}
		new = ft_init_token(str, token->type, token->pos, token->expand_flag);
		if (!new)
			return (double_free(ret, str), NULL);
		new->type_error = token->type_error;
		new->flag_error = token->flag_error;
		addlast_token(&ret, new);
		token = token->next;
	}
	return (ret);
}

/*Fonction pour compter le nombre d'args*/
static int	nb_args(t_arg *arg)
{
	int	nbr;

	nbr = 0;
	while (arg)
	{
		nbr++;
		arg = arg->next;
	}
	return (nbr);
}

/*Fonction pour free un tableau*/
static void	free_tab(char **tab)
{
	int	idx;

	if (!tab)
		return ;
	idx = 0;
	while (tab[idx])
	{
		if (tab[idx])
			free(tab[idx]);
		idx++;
	}
	free(tab);
}

/*Fonction pour mettre tous les args dans un tableau*/
char	**tab_of_args(t_arg *args)
{
	char	**tab;
	int		i;

	i = nb_args(args);
	if (i == 0)
		return (NULL);
	tab = ft_calloc(i + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (args)
	{
		tab[i] = ft_strdup(args->value);
		if (!tab[i])
			return (free_tab(tab), NULL);
		i++;
		args = args->next;
	}
	tab[i] = NULL;
	return (tab);
}
