/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 15:42:41 by gino              #+#    #+#             */
/*   Updated: 2024/07/31 15:35:58 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*Cree et initalise un nouvel argument*/

static t_arg	*init_new_arg(char *value, int ttype)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->value = value;
	new->token_type = ttype;
	new->next = NULL;
	return (new);
}

/*Ajouter un nouvel argument a la liste d'arguments*/
static void	add_arg(t_arg	**args, t_arg *new)
{
	t_arg	*lst;

	if (*args == NULL)
		*args = new;
	else
	{
		lst = *args;
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
}

/*Cree une liste d'arguments*/
t_arg	*create_args_list(t_token *token)
{
	t_arg	*new;
	t_arg	*ret;

	ret = NULL;
	while (token && token->type != PIPE)
	{
		if (!(token->refered_flag) && ft_isop(token->value)
			&& *token->value == '\0')
		{
			new = init_new_arg(ft_strdup(token->value), token->type);
			if (!new)
				return (free_args_list(&ret), NULL);
			add_arg(&ret, new);
		}
		else if (!(token->refered_flag) && !(ft_isop(token->value))
			&& token->value != NULL)
		{
			new = init_new_arg(ft_strdup(token->value), token->type);
			if (!new)
				return (free_args_list(&ret), NULL);
			add_arg(&ret, new);
		}
		token = token->next;
	}
	return (ret);
}

/*Fonction pour free la liste d'arguments*/
void	free_args_list(t_arg **lst)
{
	t_arg	*current;
	t_arg	*next;

	current = *lst;
	while (current)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
}
