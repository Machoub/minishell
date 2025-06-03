/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 01:31:09 by gdoubren          #+#    #+#             */
/*   Updated: 2024/07/30 21:26:06 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui met a jour un export*/
static int	export_update(t_env *prev, char *input, char *value)
{
	if (prev->next->value)
	{
		free(prev->next->value);
		prev->next->value = value;
	}
	if (prev->next->name)
	{
		free(prev->next->name);
		prev->next->name = input;
	}
	return (SUCCESS);
}

/*Fonction qui lie l'export*/
static void	link_export(t_env *prev, t_env *exp, t_env **exports)
{
	if (prev)
	{
		if (exp)
			exp->next = prev->next;
		prev->next = exp;
	}
	else
	{
		if (exp)
			exp->next = *exports;
		*exports = exp;
	}
}

static t_env	*get_correct_export(t_env *exports, char *key)
{
	t_env	*current;
	t_env	*prev;

	prev = NULL;
	current = exports;
	while (current && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	return (prev);
}

/*Fonction qui ajoute l'export donne*/
static int	add_given_export(t_env *prev, char *input, char *key, char *val)
{
	if (prev && prev->next && !(ft_strcmp(prev->next->key, key)))
	{
		if (!(ft_strchr(input, '=')))
		{
			free(key);
			free(val);
			free(input);
			return (-1);
		}
		export_update(prev, input, val);
		free(key);
		return (-1);
	}
	return (SUCCESS);
}

/*Fonction qui ajoute un nouvel export*/
int	add_export(t_env **exports, char *name, char *key, char *value)
{
	t_env	*env;
	char	*newk;
	char	*newv;
	char	*input;

	newk = ft_strdup(key);
	if (!newk)
		return (SUCCESS);
	newv = ft_strdup(value);
	if (!newv)
		return (free(newk), SUCCESS);
	input = ft_strdup(name);
	if (!input)
		return (free(newk), free(newv), SUCCESS);
	env = init_env(input, newk, newv);
	if (!env)
		return (free(newk), free(newv), free(input), SUCCESS);
	if (!*exports)
		return (*exports = env, SUCCESS);
	if (add_given_export(get_correct_export(*exports, newk), input, newk,
			newv) == FAIL)
		return (free(env), SUCCESS);
	link_export(get_correct_export(*exports, newk), env, exports);
	return (SUCCESS);
}
