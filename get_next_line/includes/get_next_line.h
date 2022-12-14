/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:21:04 by pfrances          #+#    #+#             */
/*   Updated: 2022/12/14 13:14:13 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define GNL_BUFFER_SIZE 1024
# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../libft/includes/libft.h"

typedef enum e_success
{
	ERROR,
	SUCCESS,
	CONTINUE
}		t_success;

char	*get_next_line(int fd);
char	*ft_strjoin_with_free(char *s1, char const *s2);
char	*ft_strndup(const char *s, size_t n);

#endif