/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 15:46:41 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/09 22:23:52 by pfrances         ###   ########.fr       */
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
	cmd->redirect = malloc(sizeof(t_redirect *)
			* (count->input_output_cnt + 1));
	cmd->args = malloc(sizeof(char *) * (count->args_cnt + 1));
	if (cmd->redirect == NULL || cmd->args == NULL)
	{
		free(cmd->redirect);
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

t_cmd	*init_cmd(t_token *token)
{
	t_cmd	*cmd;

	token->lexem = expand_env_var(token->lexem);
	if (g_state.error_state != NO_ERROR)
		return (NULL);
	expend_wildcards(&token->lexem);
	if (g_state.error_state != NO_ERROR)
		return (NULL);
	cmd = allocate_cmd(token->lexem);
	if (cmd == NULL)
		return (NULL);
	cmd->all_path = get_env_path_array();
	if (g_state.error_state != NO_ERROR)
		return (NULL);
	set_input_output_args(cmd, token->lexem);
	if (g_state.error_state != NO_ERROR)
		return (NULL);
	cmd->path = get_cmd_path(cmd->args[0], cmd->all_path);
	cmd->input_fd = STDIN_FILENO;
	cmd->input_fd_save = -1;
	cmd->output_fd = STDOUT_FILENO;
	cmd->output_fd_save = -1;
	cmd->builtin_type = check_builtin_type(cmd->args);
	return (cmd);
}
