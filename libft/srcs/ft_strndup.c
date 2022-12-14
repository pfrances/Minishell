/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 11:28:12 by pfrances          #+#    #+#             */
/*   Updated: 2022/12/07 11:34:14 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s) + 1;
	if (size > n)
		size = n + 1;
	dup = malloc(sizeof(char) * (size));
	if (dup != NULL)
		ft_strlcpy(dup, s, size);
	return (dup);
}
