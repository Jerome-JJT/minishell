/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahuber <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 15:42:46 by ahuber            #+#    #+#             */
/*   Updated: 2022/01/22 15:42:48 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_single_start(t_command *cmds, t_builtin *bt, char **envp);
static void	ft_fork_commands(t_command *cmds,
				t_builtin *bt, char **envp, int nbcmd);
static void	ft_wait_forks(int *pids, int nbcmd);
static void	ft_prep_dup(t_command *cmds, int i, int nbcmd);

void	ft_launch_commands(t_command *cmds,
				t_builtin *bt, char **envp, int nbcmd)
{
	if (nbcmd == 1)
	{
		ft_single_start(cmds, bt, envp);
	}
	else if (nbcmd >= 2)
	{
		ft_fork_commands(cmds, bt, envp, nbcmd);
	}
}

static void	ft_single_start(t_command *cmds, t_builtin *bt, char **envp)
{
	int	bakstdin;
	int	bakstdout;

	if (cmds[0].nbarg > 0)
	{
		bakstdin = dup(0);
		bakstdout = dup(1);
		ft_prep_dup(cmds, 0, 1);
		ft_search_command(cmds, bt, envp, 0);
		dup2(bakstdin, 0);
		dup2(bakstdout, 1);
		close(bakstdin);
		close(bakstdout);
	}
}

static void	ft_fork_commands(t_command *cmds,
		t_builtin *bt, char **envp, int nbcmd)
{
	int	i;
	int	*pids;

	pids = ft_calloc(nbcmd, sizeof(int));
	i = -1;
	while (++i < nbcmd)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			ft_prep_dup(cmds, i, nbcmd);
			ft_search_command(&cmds[i], bt, envp, 1);
			free(pids);
			close(cmds[i].fdin);
			close(cmds[i].fdout);
			ft_free_commands(cmds, nbcmd);
			ft_free_builtins(bt);
			exit(0);
		}
		if (cmds[i].fdin != 0)
			close(cmds[i].fdin);
		if (cmds[i].fdout != 1)
			close(cmds[i].fdout);
	}
	ft_wait_forks(pids, nbcmd);
}

static void	ft_prep_dup(t_command *cmds, int i, int nbcmd)
{
	int	other;

	other = i + 1;
	while (other < nbcmd)
	{
		close(cmds[other].fdin);
		close(cmds[other].fdout);
		other++;
	}
	if (cmds[i].fdin != 0)
	{
		dup2(cmds[i].fdin, 0);
		close(cmds[i].fdin);
	}
	if (cmds[i].fdout != 1)
	{
		dup2(cmds[i].fdout, 1);
		close(cmds[i].fdout);
	}
}

static void	ft_wait_forks(int *pids, int nbcmd)
{
	int	i;
	int	status;

	i = 0;
	while (i < nbcmd)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		g_exit_stat = WEXITSTATUS(status);
	free(pids);
}
