/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 00:32:11 by gdoubren          #+#    #+#             */
/*   Updated: 2024/09/04 14:22:58 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
/*Fonction qui ajoute un export a la liste*/
void	add_export_to_lst(t_env **exports, t_env *new)
{
	t_env	*current;
	t_env	*prev;

	if (!exports)
	{
		*exports = new;
		return ;
	}
	current = *exports;
	prev = NULL;
	while (current && ft_strcmp(current->key, new->key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (!prev)
	{
		new->next = *exports;
		*exports = new;
	}
	else
	{
		prev->next = new;
		new->next = current;
	}
}

/*Fonction qui cree un export par defaut*/
t_env	*create_export(void)
{
	t_env	*exp;
	t_env	*ret;

	ret = NULL;
	exp = create__new_env("PWD=", "PWD", getcwd(NULL, 0));
	if (!exp)
		return (free_envs(&ret), NULL);
	add_export_to_lst(&ret, exp);
	exp = create__new_env("SHLVL=", "SHLVL", "1");
	if (!exp)
		return (free_envs(&ret), NULL);
	add_export_to_lst(&ret, exp);
	exp = create__new_env(NULL, "OLDPWD", NULL);
	if (!exp)
		return (free_envs(&ret), NULL);
	add_export_to_lst(&ret, exp);
	return (ret);
}

/*Fonction qui cree une liste d'export*/
t_env	*create_export_list(char **env)
{
	t_env	*ret;
	t_env	*exp;
	int		i;

	ret = NULL;
	i = 0;
	while (env[i])
	{
		exp = env_from_input(env[i]);
		if (!exp)
			return (free_envs(&ret), NULL);
		add_export_to_lst(&ret, exp);
		i++;
	}
	if (!ret)
		ret = create_export();
	return (ret);
}

/*Fonction qui affiche les variables exportees*/
void	print_exports(t_data *data)
{
	t_env	*current;

	if (!data)
		return ;
	current = data->exports;
	while (current)
	{
		ft_putstr_fd("export ", 1);
		if (current->key)
			ft_putstr_fd(current->key, 1);
		if (ft_strchr(current->name, '='))
		{
			ft_putstr_fd("=\"", 1);
			if (current->value)
				ft_putstr_fd(current->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		current = current->next;
	}
}

/*Fonction qui enleve un export*/
void	remove_export(t_env **exports, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!*exports)
		return ;
	current = *exports;
	prev = NULL;
	while (current && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (!current)
		return ;
	if (prev == NULL)
		*exports = current->next;
	else
		prev->next = current->next;
	free(current->key);
	free(current->value);
	if (current->name)
		free(current->name);
	free(current);
}
