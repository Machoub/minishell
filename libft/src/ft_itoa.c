/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:41:18 by machouba          #+#    #+#             */
/*   Updated: 2024/05/09 14:40:24 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	int	i;
	int	q;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n > 0)
	{
		q = n % 10;
		n = n - q;
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*toa;

	len = ft_intlen(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	toa = (char *)ft_calloc((len + 1), sizeof(char));
	if (!toa)
		return (NULL);
	if (n < 0)
	{
		toa[0] = '-';
		n = -n;
	}
	while (n > 9)
	{
		toa[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	toa[len - 1] = n % 10 + '0';
	return (toa);
}
