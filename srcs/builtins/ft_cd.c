/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 17:38:09 by machouba          #+#    #+#             */
/*   Updated: 2024/09/04 14:23:28 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui renvoie si une cle existe*/
static bool	there_is_key(t_env *env, char *key)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (!(ft_strcmp(current->key, key)))
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

/*Fonction qui renvoie le path a atteindre*/
static char	*get_target(t_arg *args, t_env *envs)
{
	char	*path;

	path = NULL;
	if (args && args->next && !(ft_strcmp(args->next->value, "~")))
	{
		if (!(there_is_key(envs, "HOME")))
			return (ft_putstr_fd("minichill: cd: HOME not set\n", 2), NULL);
		path = get_env(envs, "HOME");
		if (!path)
			return (NULL);
		return (ft_strdup(path));
	}
	else if (args && args->next && !(ft_strcmp(args->value, "-")))
	{
		path = get_env(envs, "OLDPWD");
		ft_putstr_fd(path, 1);
		ft_putstr_fd("\n", 1);
		return (path);
	}
	return (path);
}

/*Fonction qui recupere le bon path*/
static char	*get_path(t_arg *args, t_env *envs)
{
	char	*path;

	path = NULL;
	if (args && args->next && (!(ft_strcmp(args->next->value, "~"))
			|| !(ft_strcmp(args->next->value, "-"))))
	{
		path = get_target(args, envs);
		return (path);
	}
	else if (args && args->next == NULL)
	{
		if (!(there_is_key(envs, "HOME")))
			return (ft_putstr_fd("minichill: cd: HOME not set\n", 2), NULL);
		path = get_env(envs, "HOME");
		if (!path)
			return (ft_strdup("."));
	}
	else if (args && args->next && !(ft_strcmp(args->next->value, "--")))
		path = get_env(envs, "OLDPWD");
	else if (args && args->next)
		path = ft_strdup(args->next->value);
	return (path);
}

/*Fonction qui compte les args*/
static int	args_count(t_arg *args)
{
	int	res;

	res = 0;
	while (args)
	{
		res++;
		args = args->next;
	}
	return (res);
}

/*Fonction qui change de repertoire (cd)*/
int	ft_cd(t_env *envs, t_command *cmd)
{
	t_arg	*arg;
	char	*path;
	char	*dir;

	arg = cmd->args_lst;
	if (!arg || !arg->value)
		return (1);
	if (2 < args_count(arg))
		return (ft_putstr_fd("minichill: cd: too many arguments\n", 2), 1);
	if (arg && arg->next && !(ft_strncmp(arg->next->value, "---", 3)))
		return (ft_putstr_fd("minichill: cd: --: invalid option\n", 2), 2);
	path = get_path(arg, envs);
	if (!path)
		return (1);
	dir = getcwd(NULL, 0);
	if (!dir && path && path[0] != '/')
		return (ft_putstr_fd("minichill: cd: ", 2), perror(dir), free(path), 1);
	if (chdir(path) == -1)
		return (ft_putstr_fd("minichill: cd:", 2), perror(path), free(path),
			free(dir), 1);
	free(path);
	set_env(&envs, ft_strdup("OLDPWD"), ft_strdup(dir));
	free(dir);
	dir = getcwd(NULL, 0);
	return (set_env(&envs, ft_strdup("PWD"), ft_strdup(dir)), free(dir), 0);
}
