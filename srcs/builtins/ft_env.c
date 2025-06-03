/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gino <gino@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:27:06 by gino              #+#    #+#             */
/*   Updated: 2024/08/02 17:48:45 by gino             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui updates les variables d'env*/
static int	maj_var(t_env **envs, char *key, char *value)
{
	t_env	*env;

	env = *envs;
	while (env)
	{
		if (!(ft_strncmp(env->key, key, ft_strlen(key))))
		{
			if (env->value)
				free(env->value);
			env->value = value;
			if (key)
				free(key);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (-1);
}

/*Fonction qui etablit un env*/
int	set_env(t_env **envs, char *key, char *value)
{
	t_env	*env;
	t_env	*tmp;

	if (!key || !value)
		return (SUCCESS);
	if (maj_var(envs, key, value) == SUCCESS)
		return (SUCCESS);
	env = init_env(NULL, key, value);
	if (!env)
		return (-1);
	if (!*envs)
		*envs = env;
	else
	{
		tmp = *envs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = env;
	}
	return (SUCCESS);
}

/*Fonction qui supprime un env*/
void	delete_env(t_env **envs, char *key)
{
	t_env	*current;
	t_env	*prev;

	current = *envs;
	prev = NULL;
	while (current)
	{
		if (!(ft_strncmp(current->key, key, ft_strlen(key))))
		{
			if (prev)
				prev->next = current->next;
			else
				*envs = current->next;
			if (current->key)
				free(current->key);
			if (current->value)
				free(current->value);
			if (current->name)
				free(current->name);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

/*Fonction qui recupere l'env en parametre*/
char	*get_env(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!(ft_strcmp(tmp->key, key)))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_env(t_data *data)
{
	t_env	*current;

	if (!data)
		return (1);
	current = data->envs;
	while (current)
	{
		ft_putstr_fd(current->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(current->value, 1);
		ft_putstr_fd("\n", 1);
		current = current->next;
	}
	return (0);
}
