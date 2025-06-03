/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:28:48 by machouba          #+#    #+#             */
/*   Updated: 2024/01/19 15:29:45 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lenhexa(unsigned int x)
{
	int	len;

	len = 0;
	while (x != 0)
	{
		len++;
		x = x / 16;
	}
	return (len);
}

void	ft_puthexa(unsigned int x, const char c)
{
	if (x >= 16)
	{
		ft_puthexa((x / 16), c);
		ft_puthexa((x % 16), c);
	}
	else
	{
		if (x <= 9)
			ft_putchar_fd((x + '0'), 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd((x - 10 + 'a'), 1);
			if (c == 'X')
				ft_putchar_fd((x - 10 + 'A'), 1);
		}
	}
}

int	ft_printhexa(unsigned int x, const char c)
{
	if (x == 0)
		return (write(1, "0", 1));
	else
		ft_puthexa(x, c);
	return (ft_lenhexa(x));
}
