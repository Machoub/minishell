/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 02:00:14 by gdoubren          #+#    #+#             */
/*   Updated: 2024/07/30 21:27:19 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui check le nom de la variable*/
static bool	check_name(char *name)
{
	int	i;

	i = 0;
	if (!name || !name[0] || isdigit(name[0]))
		return (FALSE);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*Fonction qui check l'identifier*/
static void	check_identifier(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

/*Fonction qui ajoute je sais pas quoi*/
static int	add_it(t_env **envs, t_env *new, char *newk, char *newv)
{
	t_env	*current;
	t_env	*prev;

	current = *envs;
	if (!current)
		return (*envs = new, SUCCESS);
	prev = current;
	while (current)
	{
		if (!(ft_strcmp(current->key, newk)))
		{
			if (current->value)
				free(current->value);
			current->value = newv;
			if (newk)
				free(newk);
			return (free(new), SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	prev->next = new;
	return (SUCCESS);
}

/*Fonction qui ajoute a l'env ou qui ajoute l'env*/
static void	add_env(t_env **envs, char *key, char *value)
{
	t_env	*env;
	char	*newk;
	char	*newv;

	newk = ft_strdup(key);
	if (!newk)
		return ;
	newv = ft_strdup(value);
	if (!newv)
		return (free(newk));
	env = init_env(NULL, newk, newv);
	if (!env)
		return (free(newk), free(newv));
	add_it(envs, env, newk, newv);
}

/*Fonction qui gere l'input je pense*/
int	handle_input(t_data *data, char *input)
{
	char	*key;
	char	*val;

	key = ft_substr(input, 0, ft_strchr(input, '=') - input);
	if (!(check_name(key)))
		return (free(key), check_identifier(input), -1);
	val = ft_substr(input, ft_strchr(input, '=') - input + 1,
			ft_strlen(input));
	if (ft_strchr(input, '=') != NULL)
		add_env(&data->envs, key, val);
	if (key && key[0] == '_' && !(key[1]))
		return (free(key), free(val), SUCCESS);
	add_export(&data->exports, input, key, val);
	free(key);
	free(val);
	return (SUCCESS);
}
