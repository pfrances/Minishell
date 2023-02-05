/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 13:42:33 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/05 19:10:22 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*do_allocation(t_cmd_cnt *count)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		g_state.error_state = ALLOCATION_FAILED;
		return (NULL);
	}
	cmd->input_output = malloc(sizeof(t_input_output *)
			* (count->input_output_cnt + 1));
	cmd->args = malloc(sizeof(char *) * (count->args_cnt + 1));
	if (cmd->input_output == NULL || cmd->args == NULL)
	{
		free(cmd->input_output);
		free(cmd->args);
		g_state.error_state = ALLOCATION_FAILED;
	}
	return (cmd);
}

void	skip_and_check_next_token(char *lexem, size_t *i)
{
	size_t	j;

	if (lexem[*i] == '<' || lexem[*i] == '>')
	{
		if (lexem[*i] == lexem[*i + 1])
			(*i)++;
		(*i)++;
	}
	while (ft_isspace(lexem[*i]) == true)
		(*i)++;
	while (lexem[*i] != '\0' && !ft_isspace(lexem[*i])
		&& (lexem[*i] != '<' || lexem[*i] != '>'))
	{
		if (lexem[*i] == '"' || lexem[*i] == '\'')
		{
			j = 0;
			while (lexem[*i + j] != lexem[*i])
					j++;
			*i += j;
		}
		(*i)++;
	}
	while (ft_isspace(lexem[*i]) == true)
		(*i)++;
}

t_cmd	*allocate_cmd(char *lexem)
{
	size_t		i;
	t_cmd_cnt	count;

	count.input_output_cnt = 0;
	count.args_cnt = 0;
	i = 0;
	while (lexem[i] != '\0')
	{
		if (lexem[i] == '<' || lexem[i] == '>')
			count.input_output_cnt++;
		else
			count.args_cnt++;
		skip_and_check_next_token(lexem, &i);
	}
	return (do_allocation(&count));
}

t_cmd	*init_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;

	expend_wildcards(&lexer->current_token->lexem);
	cmd = allocate_cmd(lexer->current_token->lexem);
	if (cmd == NULL)
		return (NULL);
	cmd->all_path = lexer->all_path;
	cmd->envp = lexer->envp;
	set_input_output_args(cmd, lexer->current_token->lexem);
	cmd->path = get_cmd_path(cmd->args[0], cmd->all_path);
	cmd->input_fd = STDIN_FILENO;
	cmd->input_fd_save = -1;
	cmd->output_fd = STDOUT_FILENO;
	cmd->output_fd_save = -1;
	return (cmd);
}

t_ast_node	*create_node(t_lexer *lexer)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (node == NULL)
	{
		g_state.error_state = ALLOCATION_FAILED;
		return (NULL);
	}
	node->token = lexer->current_token;
	if (node->token->type == COMMAND)
		node->cmd = init_cmd(lexer);
	else
		node->cmd = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
