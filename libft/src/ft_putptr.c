/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:29:39 by machouba          #+#    #+#             */
/*   Updated: 2024/01/19 15:29:37 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_lenptr(unsigned long p)
{
	int	len;

	len = 0;
	while (p != 0)
	{
		len++;
		p = p / 16;
	}
	return (len);
}

void	ft_putptr(unsigned long p)
{
	if (p >= 16)
	{
		ft_putptr(p / 16);
		ft_putptr(p % 16);
	}
	else
	{
		if (p <= 9)
			ft_putchar_fd((p + '0'), 1);
		else
			ft_putchar_fd((p - 10 + 'a'), 1);
	}
}

int	ft_printptr(unsigned long long p)
{
	int	len;

	len = 0;
	if (p == 0)
		len += write(1, "(nil)", 5);
	else
	{
		len += write(1, "0x", 2);
		ft_putptr(p);
		len += ft_lenptr(p);
	}
	return (len);
}
