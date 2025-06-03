/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:40:14 by machouba          #+#    #+#             */
/*   Updated: 2024/05/08 10:42:55 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*i;

	i = (char *)s + ft_strlen(s);
	while (*i != (char)c)
	{
		if (i == s)
			return (NULL);
		i--;
	}
	return (i);
}
