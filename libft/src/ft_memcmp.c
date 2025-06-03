/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:25:21 by machouba          #+#    #+#             */
/*   Updated: 2023/11/14 17:08:18 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;
	size_t				i;

	i = 0;
	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (ptr1[i] == ptr2[i])
			i++;
		else
			return (ptr1[i] - ptr2[i]);
	}
	return (0);
}
