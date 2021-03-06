#include "minishell.h"

typedef struct s_envlst
{
	char			*val;
	struct s_envlst	*next;
}	t_envlst;


t_envlst	*env_lstnew(char *content)
{
	t_envlst	*new_lst;

	if (content == NULL)
		return (NULL);

	new_lst = ft_calloc(1, sizeof(t_envlst));

	if (new_lst == NULL)
		return (NULL);

	new_lst->val = content;
	new_lst->next = NULL;
	return (new_lst);
}



void	env_lstadd_back(t_envlst **alst, t_envlst *new)
{
	t_envlst	*lastlst;

	if (new == NULL)
		return ;
	lastlst = *alst;
	while (lastlst != NULL && lastlst->next != NULL)
		lastlst = lastlst->next;

	if (lastlst != NULL)
		lastlst->next = new;
	else
		*alst = new;
}

t_envlst	*env_import(char **env)
{
	int			i;
	t_envlst	*newenv;

	newenv = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		env_lstadd_back(&newenv, env_lstnew(ft_strdup(env[i])));
		i++;
	}
	return (newenv);
}

void	env_print(t_envlst *env)
{
	while(env != NULL)
	{
		ft_putendl_fd(env->val, 1);
		env = env->next;
	}
}

/*
void	eval_lstadd_child(t_envlst **alst, t_envlst *child)
{
	t_envlst	*lastlst;
	t_envlst	*new;

	lastlst = *alst;
	while (lastlst != NULL && lastlst->next != NULL)
		lastlst = lastlst->next;

	new = ft_calloc(1, sizeof(t_envlst));
	if (new == NULL)
		return ;
	new->op = NULL;
	new->child = child;
	
	if (lastlst != NULL)
		lastlst->next = new;
	else
		*alst = new;
}*/