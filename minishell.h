/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:34:20 by pfrances          #+#    #+#             */
/*   Updated: 2022/12/14 16:48:47 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "./libft/includes/libft.h"
# include "./ft_printf/includes/ft_printf.h"
# include "./get_next_line/includes/get_next_line.h"
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define OPEN_BRACKET_CHARSET "({[\"'"
# define CLOSE_BRACKET_CHARSET ")}]\"'"
# define SPACES_CHARSET " \n\t\v\f\r"

/*			lexer.c					*/
int		lexer(void);

/*			ft_split_charset.c		*/
char	**ft_split_charset(char *input, const char *charset);

/*			frees.c					*/
void	free_array(void **array);

#endif
