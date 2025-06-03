/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: machouba <machouba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:12:40 by machouba          #+#    #+#             */
/*   Updated: 2024/01/19 15:29:23 by machouba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <limits.h>
# include "../inc/libft.h"

int		ft_printf(const char *format, ...);
int		ft_putchar(int c);
int		ft_printstr(char *str);
int		ft_printhexa(unsigned int x, const char c);
int		ft_putunbr(unsigned int n);
int		ft_putnbr(int n);
int		ft_printptr(unsigned long long p);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);

#endif