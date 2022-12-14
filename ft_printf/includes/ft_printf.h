/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:17:49 by pfrances          #+#    #+#             */
/*   Updated: 2022/12/07 11:44:14 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stddef.h>
# include <unistd.h>
# include <stdarg.h>
# define OPTION "cspdiuxX%%"
# define DECIMAL_BASE "0123456789"
# define HEXA_BASE_LOW "0123456789abcdef"
# define HEXA_BASE_UP "0123456789ABCDEF"

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

int		ft_printf(const char *str, ...);
size_t	print_c(char c);
size_t	print_s(char *str);
size_t	print_nbr_sign(long nb, char *base);
size_t	print_nbr_unsign(unsigned long nb, char *base);

#endif