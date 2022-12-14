/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:19:48 by pfrances          #+#    #+#             */
/*   Updated: 2022/12/06 19:23:20 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int	is_an_option(const char *ptr)
{
	size_t	i;

	i = 0;
	while (OPTION[i] != '\0')
	{
		if (OPTION[i] == *ptr)
			return (TRUE);
		i++;
	}
	if (*ptr == 'l' && *(ptr + 1) == 'd')
		return (TRUE);
	return (FALSE);
}

static void
	distribute(va_list args, size_t *result, size_t *last_pos, const char *ptr)
{
	if (*ptr == 'c')
		*result += print_c(va_arg(args, int));
	else if (*ptr == 's')
		*result += print_s(va_arg(args, char *));
	else if (*ptr == 'd' || *ptr == 'i')
		*result += print_nbr_sign(va_arg(args, int), DECIMAL_BASE);
	else if (*ptr == 'u')
		*result += print_nbr_unsign(va_arg(args, unsigned int), DECIMAL_BASE);
	else if (*ptr == 'l' && *(ptr + 1) == 'd')
		*result += print_nbr_unsign(va_arg(args, unsigned long), DECIMAL_BASE);
	else if (*ptr == 'x')
		*result += print_nbr_unsign(va_arg(args, unsigned int), HEXA_BASE_LOW);
	else if (*ptr == 'X')
		*result += print_nbr_unsign(va_arg(args, unsigned int), HEXA_BASE_UP);
	else if (*ptr == 'p')
	{
		*result += write(1, "0x", 2);
		*result += print_nbr_unsign(va_arg(args, long), HEXA_BASE_LOW);
	}
	else if (*ptr == '%')
		*result += write(1, "%%", 1);
	*last_pos += 2 + (*ptr == 'l' && *(ptr + 1) == 'd');
}

int	check_result_overflow(size_t result)
{
	if (result > __INT_MAX__)
		return (-1);
	return ((int)result);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	size_t	last_pos;
	size_t	result;

	va_start(args, str);
	i = 0;
	result = 0;
	last_pos = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			result += write(1, str + last_pos, i - last_pos);
			last_pos = i;
			if (is_an_option(&str[i + 1]) == TRUE)
				distribute(args, &result, &last_pos, &str[i + 1]);
			i++;
		}
		if (str[i + 1] == '\0')
			result += write(1, str + last_pos, i - last_pos + 1);
		i++;
	}
	va_end(args);
	return (check_result_overflow(result));
}
