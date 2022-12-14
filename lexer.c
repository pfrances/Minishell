/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:35:57 by pfrances          #+#    #+#             */
/*   Updated: 2022/12/14 17:18:57 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char **tokens)
{
	size_t	i;

	if (tokens == NULL)
		return ;
	i = 0;
	while (tokens[i] != NULL)
	{
		ft_printf("%s\n", tokens[i]);
		i++;
	}
}

char	**split_in_tokens(char *input)
{
	char	**tokens;
	size_t	nb_tokens;

	tokens = ft_split_charset(input, SPACES_CHARSET);
	if (tokens == NULL)
		return (NULL);
	return (tokens);
}

int	lexer(void)
{
	char	*input;
	char	**tokens;

	// input = get_next_line(STDIN_FILENO);
	input = readline(" > ");
	if (input == NULL)
		return (0);
	tokens = split_in_tokens(input);
	if (tokens == NULL)
		return (1);
	print_tokens(tokens);
	free(input);
	free_array((void **)tokens);
	return (0);
}
