/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 19:15:36 by pfrances          #+#    #+#             */
/*   Updated: 2023/02/25 17:52:14 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_dir_env_value(char *home_dir, char *old_dir)
{
	free(home_dir);
	free(old_dir);
}

bool	go_to_home(char *home_dir_name, char **dir_to_go)
{
	if (home_dir_name == NULL)
	{
		if (g_state.error == NO_ERROR)
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
		return (false);
	}
	*dir_to_go = home_dir_name;
	return (true);
}

bool	go_to_previous_dir(char *old_dir, char **dir_to_go)
{
	if (old_dir == NULL || old_dir[0] == '\0')
	{
		if (g_state.error == NO_ERROR)
			write(STDERR_FILENO, "cd: OLDPWD not set\n", 19);
		return (false);
	}
	*dir_to_go = old_dir;
	return (true);
}

void	move_and_actualise_env(char *dir_to_go, bool print_pwd)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	update_env_entry(ft_strdup("OLDPWD"), cwd);
	if (chdir(dir_to_go) != 0)
	{
		perror(dir_to_go);
		g_state.exit_status = 1;
	}
	else
	{
		cwd = getcwd(NULL, 0);
		update_env_entry(ft_strdup("PWD"), cwd);
		if (print_pwd == true)
			ft_putendl_fd(cwd, STDOUT_FILENO);
	}
}

void	builtin_cd(t_cmd *cmd)
{
	char	*home_dir;
	char	*old_dir;
	char	*dir_to_go;
	bool	print_pwd;

	home_dir = get_env_value("HOME");
	old_dir = get_env_value("OLDPWD");
	print_pwd = false;
	if (cmd->args[1] == NULL)
	{
		if (go_to_home(home_dir, &dir_to_go) == false)
			return (free_dir_env_value(home_dir, old_dir));
	}
	else if (cmd->args[1][0] == '-' && cmd->args[1][1] == '\0')
	{
		if (go_to_previous_dir(old_dir, &dir_to_go) == false)
			return (free_dir_env_value(home_dir, old_dir));
		print_pwd = true;
	}
	else
		dir_to_go = cmd->args[1];
	move_and_actualise_env(dir_to_go, print_pwd);
	free_dir_env_value(home_dir, old_dir);
	update_all_env();
}
