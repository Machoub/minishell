/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:58:46 by machouba          #+#    #+#             */
/*   Updated: 2024/01/19 15:28:51 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_convert(va_list args, const char c)
{
	int	len;

	len = 0;
	if (c == '%')
		len += ft_printpercent();
	else if (c == 'c')
		len += ft_putchar(va_arg(args, int));
	else if (c == 's')
		len += ft_printstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		len += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		len += ft_putunbr(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		len += ft_printhexa(va_arg(args, unsigned int), c);
	else if (c == 'p')
		len += ft_printptr(va_arg(args, unsigned long));
	return (len);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	if (!format)
		return (-1);
	i = 0;
	len = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
			len += ft_convert(args, format[i++ + 1]);
		else
			len += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (len);
}
