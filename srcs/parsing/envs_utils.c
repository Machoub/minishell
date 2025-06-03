/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:07:24 by machouba          #+#    #+#             */
/*   Updated: 2024/08/30 17:22:46 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui initialise un environnement*/
t_env	*init_env(char *name, char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

/*Fonction qui passe de l'input a un environnement*/
t_env	*env_from_input(char *input)
{
	t_env	*new;
	char	*val;
	char	*key;
	char	*name;
	char	*sign;

	sign = ft_strchr(input, '=');
	if (!sign)
		return (NULL);
	key = ft_substr(input, 0, sign - input);
	if (!key)
		return (NULL);
	val = ft_strdup(sign + 1);
	if (!val)
		return (free(key), NULL);
	name = ft_strdup(input);
	if (!name)
		return (free(key), free(val), NULL);
	new = init_env(name, key, val);
	if (!new)
		return (free(key), free(val), free(name), NULL);
	return (new);
}

/*Fonction qui free toute la liste des environnements*/
void	free_envs(t_env **envs)
{
	t_env	*current;
	t_env	*next;

	current = *envs;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		if (current->name)
			free(current->name);
		free(current);
		current = next;
	}
	*envs = NULL;
}
