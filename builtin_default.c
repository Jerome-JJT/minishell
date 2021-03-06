/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_default.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:38:48 by ahuber            #+#    #+#             */
/*   Updated: 2022/01/22 15:38:52 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_unite_all(char **path_splitted, char *path);
static int	test_and_exec_cmd(char **path_splitted, t_command cmd, char **envp);
static int	builtin_end(char *add_cmd,
				char **path_splitted, t_command cmd, char **envp);

int	builtin_default(t_command cmd, char **envp)
{
	char	*path;
	char	**path_splitted;
	char	pwd[PATH_MAX];
	char	*add_cmd;

	path = ft_get_env(envp, "PATH=");
	path_splitted = ft_split(path, ':');
	add_cmd = ft_strjoin("/", cmd.args[0]);
	if (ft_strlen(cmd.args[0]) > 0 && cmd.args[0][0] != '/')
	{
		getcwd(pwd, PATH_MAX);
		ft_concat_tab(&path_splitted, ft_strdup(pwd));
	}
	ft_unite_all(path_splitted, add_cmd);
	if (ft_strlen(cmd.args[0]) > 0 && cmd.args[0][0] == '/')
		ft_concat_tab(&path_splitted, ft_strdup(cmd.args[0]));
	return (builtin_end(add_cmd, path_splitted, cmd, envp));
}

static void	ft_unite_all(char **path_splitted, char *path)
{
	char	*temp;
	int		i;

	i = 0;
	while (path_splitted[i] != NULL)
	{
		temp = ft_strjoin(path_splitted[i], path);
		free(path_splitted[i]);
		path_splitted[i] = temp;
		i++;
	}
}

static int	builtin_end(char *add_cmd,
		char **path_splitted, t_command cmd, char **envp)
{
	int	i;
	int	res;

	free(add_cmd);
	res = test_and_exec_cmd(path_splitted, cmd, envp);
	i = 0;
	while (path_splitted[i])
	{
		free(path_splitted[i]);
		i++;
	}
	free(path_splitted);
	return (res);
}

static int	test_and_exec_cmd(char **path_splitted, t_command cmd, char **envp)
{
	int	i;

	i = 0;
	while (path_splitted[i])
	{
		if ((access(path_splitted[i], F_OK)) == 0)
		{
			execve(path_splitted[i], cmd.args, envp);
			return (0);
		}
		else
			i++;
	}
	if (path_splitted[i] == NULL)
	{
		coin_error2(cmd.args[0], "command not found");
		return (127);
	}	
	return (0);
}
