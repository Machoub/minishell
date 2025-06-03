/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:46:05 by machouba          #+#    #+#             */
/*   Updated: 2024/05/09 12:28:20 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > UINT_MAX || UINT_MAX < size)
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, (nmemb * size));
	return (ptr);
}
