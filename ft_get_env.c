#include "minishell.h"

char	*ft_get_env(t_command cmd, char **envp, char *asked_var)
{
	int	i;
	int	i2;
	int	i3;
	char	*var_value;

	i = 0;
	i3 = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], asked_var, ft_strlen(asked_var)) == 0)
		{
			var_value = malloc(sizeof(char) * ft_strlen(envp[i] + 1));
			i2 = ft_strlen(asked_var) - 1;
			while (i2 < ft_strlen(envp[i]))
			{
				var_value[i3]  = envp[i][i2];
				i3++;
				i2++;
			}
		}
		i++;
	}
	return (var_value);
}
