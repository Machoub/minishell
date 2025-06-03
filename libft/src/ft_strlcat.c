/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:27:29 by machouba          #+#    #+#             */
/*   Updated: 2023/11/21 14:20:14 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_size;
	size_t	src_size;

	if (size == 0 && !dst)
		return (ft_strlen(src));
	i = 0;
	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dst_size >= size)
		return (src_size + size);
	while (src[i] && i < (size - dst_size - 1))
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (src_size + dst_size);
}
