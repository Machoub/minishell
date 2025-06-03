/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 16:17:28 by machouba          #+#    #+#             */
/*   Updated: 2024/07/31 14:49:43 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strndup(char *s, int size)
{
	char	*s2;
	int		i;
	int		len;

	len = ft_strlen(s);
	if (len == 0)
		return (NULL);
	s2 = malloc(sizeof(char) * (size + 1));
	if (!s || !s2)
		return (NULL);
	i = 0;
	while (s[i] && i < size)
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_strsjoin(char *the_str, char *str_to_add)
{
	int		the_str_len;
	int		str_to_add_len;
	int		new_len;
	char	*new;

	if (the_str == NULL && str_to_add == NULL)
		return (NULL);
	the_str_len = ft_strlen(the_str);
	str_to_add_len = ft_strlen(str_to_add);
	new_len = the_str_len + str_to_add_len;
	new = malloc(sizeof(char) * (new_len + 1));
	if (!new)
		return (NULL);
	if (the_str)
		ft_strlcpy(new, the_str, the_str_len + 1);
	if (str_to_add)
		ft_strlcpy(new + the_str_len, str_to_add, str_to_add_len + 1);
	new[new_len] = '\0';
	if (the_str)
		free(the_str);
	if (str_to_add)
		free(str_to_add);
	return (new);
}

int	is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (TRUE);
	return (FALSE);
}

int	ft_isquote(char c)
{
	if (c == DOUBLE_QUOTES || c == SINGLE_QUOTE)
		return (TRUE);
	return (FALSE);
}

int	ft_is_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
}
