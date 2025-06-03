/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:10:55 by machouba          #+#    #+#             */
/*   Updated: 2023/11/14 17:08:43 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	letter;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	letter = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == letter)
			return (ptr + i);
		i++;
	}
	return (NULL);
}
