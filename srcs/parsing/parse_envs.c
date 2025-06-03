/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 17:29:50 by machouba          #+#    #+#             */
/*   Updated: 2024/09/04 15:14:58 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui ajoute un nouvel environnement a la liste*/
static void	new_env(t_env **envs, t_env *new)
{
	t_env	*current;

	if (!*envs)
	{
		*envs = new;
		return ;
	}
	current = *envs;
	while (current->next)
		current = current->next;
	current->next = new;
}

/*Fonction qui cree un nouvel environnement*/
t_env	*create__new_env(char *var, char *key, char *value)
{
	t_env	*new;
	char	*newvar;
	char	*newk;
	char	*newv;

	newk = ft_strdup(key);
	if (!newk)
		return (NULL);
	newv = ft_strdup(value);
	if (!newv)
		return (free(newk), NULL);
	newvar = ft_strdup(var);
	if (!newvar)
		return (free(newk), free(newv), NULL);
	new = init_env(newvar, newk, newv);
	if (!new)
		return (free(newk), free(newv), free(newvar), NULL);
	return (new);
}

/*Fonction qui fait l'env par default (pas compris)*/
t_env	*default_env(void)
{
	t_env	*new;
	t_env	*res;

	res = NULL;
	new = create__new_env(NULL, "PWD", getcwd(NULL, 0));
	if (!new)
		return (free_envs(&res), NULL);
	new_env(&res, new);
	new = create__new_env(NULL, "SHLVL", "1");
	if (!new)
		return (free_envs(&res), NULL);
	new_env(&res, new);
	new = create__new_env(NULL, "_", "/usr/bin/env");
	if (!new)
		return (free_envs(&res), NULL);
	new_env(&res, new);
	return (res);
}

/*Fonction qui cree une liste d'environnements*/
t_env	*creates_envs_list(char **env)
{
	t_env	*new;
	t_env	*ret;
	int		i;

	ret = NULL;
	i = 0;
	while (env[i])
	{
		new = env_from_input(env[i]);
		if (!new)
			return (free_envs(&ret), NULL);
		new_env(&ret, new);
		i++;
	}
	if (!ret)
		ret = default_env();
	return (ret);
}
