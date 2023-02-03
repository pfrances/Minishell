/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_input_output_args.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:56:04 by pfrances          #+#    #+#             */
/*   Updated: 2023/01/31 19:45:00 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char *cmd_token)
{
	size_t	i;
	size_t	j;
	size_t	token_len;
	char	border_quotes;

	token_len = ft_strlen(cmd_token);
	i = 0;
	j = token_len - 1;
	border_quotes = '\0';
	while (i < j && cmd_token[i] != '\0')
	{
		if (cmd_token[i] == '\'' || cmd_token[i] == '"')
		{
			if (border_quotes != '\0' && border_quotes != cmd_token[i])
				return ;
			border_quotes = cmd_token[i];
			while (cmd_token[j] != cmd_token[i])
				j--;
			ft_memmove(&cmd_token[i], &cmd_token[i + 1], token_len - i);
			cmd_token[--token_len] = '\0';
			j--;
			ft_memmove(&cmd_token[j], &cmd_token[j + 1], token_len - j);
			cmd_token[--token_len] = '\0';
			j--;
		}
		else
			i++;
	}
}

char	*get_cmd_token(char *str, size_t *lexem_index)
{
	size_t	i;
	size_t	j;
	char	*cmd_token;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]) == true || str[i] == '<' || str[i] == '>')
			break ;
		if (str[i] == '"' || str[i] == '\'')
		{
			j = 1;
			while (str[i + j] != str[i])
				j++;
			i += j;
		}
		i++;
	}
	cmd_token = ft_strndup(str, i);
	if (cmd_token == NULL)
		g_state.status = ALLOCATION_FAILED;
	*lexem_index += i;
	remove_quotes(cmd_token);
	return (cmd_token);
}

t_input_output	*set_input_output(char *lexem, size_t *i)
{
	t_input_output	*result;

	result = malloc(sizeof(t_input_output));
	if (result == NULL)
	{
		g_state.status = ALLOCATION_FAILED;
		return (NULL);
	}
	if (lexem[*i] == lexem[*i + 1])
	{
		if (lexem[*i] == '<')
			result->type = STD_INPUT;
		else
			result->type = FILE_ADD_OUTPUT;
	}
	else
	{
		if (lexem[*i] == '<')
			result->type = FILE_INPUT;
		else
			result->type = FILE_OUTPUT;
	}
	(*i) += 1 + (result->type == STD_INPUT || result->type == FILE_ADD_OUTPUT);
	while (ft_isspace(lexem[*i]) == true)
		(*i)++;
	result->filename = get_cmd_token(&lexem[*i], i);
	return (result);
}

void	set_input_output_args(t_cmd *cmd, char *lexem)
{
	size_t		i;
	t_cmd_cnt	count;

	count.input_output_cnd = 0;
	count.args_cnt = 0;
	i = 0;
	while (g_state.status == NORMAL && lexem[i] != '\0')
	{
		while (ft_isspace(lexem[i]) == true)
			i++;
		if (lexem[i] == '\0')
			break ;
		if (lexem[i] == '<' || lexem[i] == '>')
			cmd->input_output[count.input_output_cnd++] = set_input_output(lexem, &i);
		else
			cmd->args[count.args_cnt++] = get_cmd_token(&lexem[i], &i);
	}
	cmd->input_output[count.input_output_cnd] = NULL;
	cmd->args[count.args_cnt] = NULL;
}
