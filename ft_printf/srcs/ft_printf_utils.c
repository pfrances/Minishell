/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 00:39:34 by pfrances          #+#    #+#             */
/*   Updated: 2022/12/06 19:23:12 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t	ft_strlen_printf(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

size_t	print_c(char c)
{
	return (write(1, &c, 1));
}

size_t	print_s(char *str)
{
	if (str != NULL)
		return (write(1, str, ft_strlen_printf(str)));
	else
		return (write(1, "(null)", 6));
}

size_t	print_nbr_sign(long nb, char *base)
{
	long	divisor;
	long	base_len;
	size_t	i;
	char	buff[65];

	i = 0;
	if (nb < 0)
	{
		nb *= (-1);
		buff[i++] = '-';
	}
	base_len = ft_strlen_printf(base);
	divisor = 1;
	while (nb / divisor >= base_len)
		divisor *= base_len;
	while (divisor > 0)
	{
		buff[i++] = base[nb / divisor];
		nb %= divisor;
		divisor /= base_len;
	}
	return (write(1, buff, i));
}

size_t	print_nbr_unsign(unsigned long nb, char *base)
{
	unsigned long	divisor;
	unsigned long	base_len;
	size_t			i;
	char			buff[65];

	i = 0;
	base_len = ft_strlen_printf(base);
	divisor = 1;
	while (nb / divisor >= base_len)
		divisor *= base_len;
	while (divisor > 0)
	{
		buff[i++] = base[nb / divisor];
		nb %= divisor;
		divisor /= base_len;
	}
	return (write(1, buff, i));
}
