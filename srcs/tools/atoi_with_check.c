/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_with_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:28:54 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/16 22:20:14 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_is_space(char c)
{
	return ((c >= '\t' && c <= '\r') || c == ' ');
}

static char	*check_sign(char *str_nbr, int *sign)
{
	if (*str_nbr == '+')
		return (str_nbr + 1);
	else if (*str_nbr == '-')
	{
		*sign = -1;
		return (str_nbr + 1);
	}
	else
		return (str_nbr);
}

long long	ft_atol_with_error_check(const char *nptr, bool *valid_nbr)
{
	long long	result;
	int			sign;
	char		*str_nbr;

	str_nbr = (char *)nptr;
	while (ft_is_space(*str_nbr))
		str_nbr++;
	sign = 1;
	str_nbr = check_sign(str_nbr, &sign);
	result = 0;
	while (*str_nbr != '\0' && ft_isdigit(*str_nbr))
	{
		if (((sign == 1) && result > (LONG_MAX - *str_nbr + '0') / 10)
			|| ((sign == -1) && result * -1 < (LONG_MIN + *str_nbr - '0') / 10))
			return (0);
		result = result * 10 + (*str_nbr - '0');
		str_nbr++;
	}
	if (*str_nbr == '\0')
		*valid_nbr = true;
	return (result * sign);
}
