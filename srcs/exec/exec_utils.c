/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:53 by machouba          #+#    #+#             */
/*   Updated: 2024/09/04 13:44:12 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// Fonction pour créer le chemin complet de la commande

static char	*create_command_path(const char *path, const char *command_name)
{
	char	*command_path;
	char	*temp_path;

	temp_path = ft_strjoin(path, "/");
	if (!temp_path)
		return (NULL);
	command_path = ft_strjoin(temp_path, command_name);
	if (!command_path)
		return (NULL);
	free(temp_path);
	return (command_path);
}

// Fonction pour libérer un tableau de chaînes de caractères

static void	free_path_list(char **path_list)
{
	int	i;

	i = 0;
	if (!path_list)
		return ;
	while (path_list[i] != NULL)
	{
		if (path_list[i])
			free(path_list[i]);
		i++;
	}
	free(path_list);
}

// Fonction pour obtenir le chemin complet d'une commande

char	*get_path_command(t_data *data, const char *command_name)
{
	char	**path_list;
	char	*command_path;
	char	*env_path;
	int		i;

	if (command_name == NULL || *command_name == '\0')
		return (ft_strdup(""));
	if (ft_strchr(command_name, '/') != NULL)
		return (ft_strdup(command_name));
	env_path = get_env(data->envs, "PATH");
	path_list = ft_split(env_path, ':');
	free(env_path);
	if (!path_list)
		return (NULL);
	i = -1;
	while (path_list[++i])
	{
		command_path = create_command_path(path_list[i], command_name);
		if (!command_path)
			return (free_path_list(path_list), NULL);
		if (access(command_path, F_OK) == 0)
			return (command_path);
		free(command_path);
	}
	return (NULL);
}

// Fonction pour créer une chaîne de caractères représentant une
//variable d'environnement

static char	*create_environment_string(const char *key, const char *value)
{
	char	*env_string;
	char	*temp;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	env_string = ft_strjoin(temp, value);
	if (!env_string)
		return (NULL);
	return (env_string);
}

// Fonction pour créer une copie du tableau des variables d'environnement

char	**create_environment(t_data *data)
{
	char	**env_array;
	t_env	*current;
	int		env_count;
	int		i;

	current = data->envs;
	if (!current)
		return (NULL);
	env_count = envs_lst_size(data->envs);
	env_array = (char **)malloc(sizeof(char *) * (env_count + 1));
	if (!env_array)
		return (NULL);
	current = data->envs;
	i = 0;
	while (current)
	{
		env_array[i] = create_environment_string(current->key, current->value);
		if (!env_array[i])
			return (free_env(env_array), NULL);
		current = current->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
