/* ************************************************************************** */
/*                                                                            */
/*                                        __                        __        */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                   \\ <_. )       CoinCoin !     ( ._> /    */
/*   By: CoinCoinTheRetour             `---'                        `---'     */
/*                                                                            */
/*   Created: 2012/12/21 12:34:56 by CoinCoinTheRetour                        */
/*   Updated: 2022/01/22 11:45:34 by ahuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Read, write
# include <unistd.h>
//INT_MAX, INT_MIN
# include <stddef.h>
//Malloc, free
# include <stdlib.h>
//Va arg
# include <stdarg.h>
//Printf, scanf
# include <stdio.h>
//Signals
# include <signal.h>
//PATH_MAX
# include <limits.h>
//terminal functions
# include <termios.h>
//waitpids
# include <sys/types.h>
# include <sys/wait.h>

# include <readline/readline.h>
# include <readline/history.h>

//Libft, gnl, ft_printf
# include <mylibft.h>

# include <sys/errno.h>

# define VAR_END " \t\n\v\f\r$'"

extern int	g_exit_stat;

typedef struct s_command {
	int		nbarg;
	int		fdin;
	int		fdout;
	char	**args;
}	t_command;

//Store "cd" -> "cd_function"
typedef struct s_builtin_cmd {
	char	*name;
	void	(*function)(t_command, char **);
}	t_builtin_cmd;

//Store x functions and x
typedef struct s_builtin {
	int				nb;
	t_builtin_cmd	**cmds;
}	t_builtin;

//main.c
int			main(int argc, char **argv, char **envp);
void		start_ascii(void);

//main_utils.c
void		ft_signal(int signo, int run);
void		ft_sig_handler(int signo);

//ft_concat_tab.c
int			ft_concat_tab(char ***ptr, char *new);

//ft_process_pipes.c
void		ft_process_pipes(char *line, t_builtin *bt, char **envp);
void		ft_free_commands(t_command *cmds, int nbcmd);

//process commands
void		ft_process_commands(t_command *cmds,
				t_builtin *bt, char **envp, int nbcmd);

void		ft_process_redirect(t_command *cmds, int nbcmd);

void		ft_process_fds(t_command *cmds, int nbcmd);

void		ft_launch_commands(t_command *cmds,
				t_builtin *bt, char **envp, int nbcmd);

void		ft_search_command(t_command *cmds,
				t_builtin *bt, char **envp, int forked);

void		process_dollar(t_command *cmds, char **envp, int nbcmd);

void		process_quote(t_command *cmds, int nbcmd);

//builtin_manage.c
t_builtin	*builtin_tab(void);
void		ft_free_builtins(t_builtin *tab);

//coin_error.c
void		coin_error2(char *err1, char *err2);
void		coin_error3(char *err1, char *err2, char *err3);
void		coin_error3m(char *err1, char *err2, char *err3);
void		coin_error_errno(char *err1);

char		*ft_get_env(char **envp, char *var);

int			builtin_default(t_command cmd, char **envp);
void		builtin_cd(t_command cmd, char **envp);
void		builtin_pwd(t_command cmd, char **envp);
void		builtin_env(t_command cmd, char **envp);
void		builtin_echo(t_command cmd, char **envp);
void		builtin_export(t_command cmd, char **envp);
void		builtin_unset(t_command cmd, char **envp);
void		builtin_exit(t_command *cmds, t_builtin *bt);

//ft_split_arg.c
typedef struct t_spliter {
	int	start_i;
	int	inside;
	int	oldinside;
	int	quote;
}	t_spliter;

char		**ft_split_arg(const char *s);

#endif
