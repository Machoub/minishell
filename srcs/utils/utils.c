/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 19:01:25 by machouba          #+#    #+#             */
/*   Updated: 2024/07/30 19:52:52 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_isappend(char *str)
{
	if (!str)
		return (FALSE);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (TRUE);
	return (FALSE);
}

static int	ft_isherdoc(char *str)
{
	if (!str)
		return (FALSE);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (TRUE);
	return (FALSE);
}

int	ft_isop(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (!str)
		return (FALSE);
	if (ft_strncmp(str, ">>", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, "<<", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, ">", len) == 0)
		return (TRUE);
	if (ft_strncmp(str, "<", len) == 0)
		return (TRUE);
	return (FALSE);
}

int	gettype(char *str)
{
	if (*str == '|')
		return (PIPE);
	if (ft_isherdoc(str) == TRUE)
		return (HEREDOC);
	if (ft_isappend(str) == TRUE)
		return (APPEND);
	if (*str == '<')
		return (LT);
	if (*str == '>')
		return (RT);
	return (WORD);
}

int	ft_isoperator(char *str)
{
	if (!str)
		return (FALSE);
	if (ft_isappend(str) || ft_isherdoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	return (FALSE);
}
