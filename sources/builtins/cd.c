/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: qtrinh <qtrinh@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/28 14:31:20 by qtrinh        #+#    #+#                 */
/*   Updated: 2024/04/17 18:29:52 by robertrinh    ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	error_check(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	printf("gaat hier\n");
	if (ft_strncmp(cmd->args[0], "-", 2) == 0)
	{
		path = ft_getenv(shell, "OLDPWD");
		printf("path is %s\n", path);
		return (FAILURE);
	}
	return (SUCCESS);
}

static void	set_home_directory(t_cmd *cmd, t_shell *shell)
{
	char	*home_dir;

	home_dir = ft_getenv(shell, "HOME");
	if (home_dir == NULL) // ! unset
	{
		// TODO error + exit code for no home in env
	}
	if (ft_strncmp(cmd->args[0], "~", 2) == 0)
	{
		home_dir = ft_strjoin(cmd->args[0], home_dir);
		printf("home_dir is now: %s\n", home_dir); // ? needed if chdir here?
	}
}

int	cd(t_cmd *cmd, t_shell *shell)
{
	char	cwd[1024];
	// char	**path;

	getcwd(cwd, 1024);
	if (error_check(cmd, shell) == FAILURE)
		printf("fail\n");
	if (cmd->arg_count == 0 || ft_strncmp(cmd->args[0], "~", 2) == 0)
		set_home_directory(cmd, shell);
	if (chdir(cwd) == -1)
	{
		printf("chdir failed :(\n"); // TODO actual error
		return (-1);
	}
	else
		printf("chdir worked!\n"); 
	return (0);
}

// TODO absolute path
// TODO accessable dir
// TODO update OLDPWD + PWD in env
// TODO cd - should show old_pwd --> OLDPWD not set error when no OLD yet
// * cd with only relative or absolute path
// ! ~ = /Users/robert aka $HOME
// ? cd with no options? how far do we need to implement?
// ? do we update the ENV from shell->envp or directly from the original?
