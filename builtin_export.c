/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:40:55 by ahuber            #+#    #+#             */
/*   Updated: 2022/01/22 15:40:56 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	search_for_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		i++;
	}
	return (0);
}

int	invalid_var(t_command cmd, char **envp)
{
	size_t	i;
	int		result;

	(void)envp;
	i = 0;
	result = 0;
	if (cmd.args[1][0] == '=' || cmd.args[1][0] == '/')
	{
		coin_error3m("export: `", cmd.args[1], "': not a valid identifier");
		result = 1;
	}
	while (cmd.args[1][i] != '=' && cmd.args[1][i])
	{
		if (cmd.args[1][i] == '/')
		{
			coin_error3m("export: `", cmd.args[1], "': not a valid identifier");
			result = 1;
		}
		if (i >= ft_strlen(cmd.args[1]) - 1)
			result = 1;
		i++;
	}
	return (result);
}

void	envp_replace(char **envp, char *new_var, int i)
{
	envp[i] = new_var;
	envp[i + 1] = NULL;
}

void	builtin_export(t_command cmd, char **envp)
{
	int		i;
	int		exists;
	char	*new_var;

	exists = 0;
	new_var = ft_strdup(cmd.args[1]);
	i = 0;
	g_exit_stat = 0;
	if (invalid_var(cmd, envp) == 0)
	{
		while (envp[i])
		{
			if (ft_strncmp(envp[i], new_var, search_for_equal(new_var)) == 0)
			{
				exists = 1;
				break ;
			}
			i++;
		}
		if (exists != 1)
			envp_replace(envp, new_var, i);
		else
			envp[i] = new_var;
	}
}
