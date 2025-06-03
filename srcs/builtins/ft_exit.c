/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:04:12 by gino              #+#    #+#             */
/*   Updated: 2024/08/08 17:38:23 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/*Fonction qui check si str est un nombre valide*/
static bool	is_nbr(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] == 0)
		i++;
	while (str[i])
	{
		if (!(isdigit(str[i])))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

/*atoi qui renvoie un long long*/
static long long	ft_atoll(char *str)
{
	long long	ret;
	int			is_neg;
	int			i;

	ret = 0;
	is_neg = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			is_neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		ret = ret * 10 + (str[i] - '0');
		i++;
	}
	return (ret * is_neg);
}

/*Fonction qui check les tailles max*/
static bool	is_overflow(char *str)
{
	char	*tmp;

	tmp = str;
	if (*tmp == '-' || *tmp == '+')
		tmp++;
	if (is_nbr(str) && ft_strlen(tmp) < 19)
		return (FALSE);
	if (ft_strlen(tmp) > 19)
		return (TRUE);
	if (is_nbr(str) && str[0] && str[0] == '-' && ft_strcmp(str,
			"-9223372036854775808") != 0)
		return (TRUE);
	return (FALSE);
}

/*Fonction qui gere l'affichage si erreur*/
static void	ft_error(char *arg, char *str, int code)
{
	ft_putstr_fd("exit\nminichill: exit: ", 2);
	if (code == 1)
		ft_putstr_fd(arg, 2);
	ft_putstr_fd(str, 2);
}

/*Fonction builtin exit*/
int	ft_exit(t_data *data, t_arg *args)
{
	int		status;
	char	*str;

	status = data->exit_return ;
	if (args->next)
	{
		str = args->next->value;
		if (!(is_nbr(str)) || is_overflow(str) == TRUE)
		{
			ft_error(str, ": numeric argument required\n", 1);
			free_all(data);
			exit(2);
		}
		else if (args_lst_len(args) > 2)
		{
			data->exit_return = 1;
			return (ft_error(str, "too many arguments\n", 2), 1);
		}
		status = ft_atoll(str) % 256;
	}
	if (data->cmd_nbr == 1)
		exit_display(data, status);
	return (reinit_data(data), status);
}
