SRCS_DIR	= ./
SRCS_FILES	= main.c split_arg.c process_pipes.c process_commands.c process_redirect.c \
		concat_tab.c builtin_manage.c builtin_cd.c builtin_pwd.c builtin_env.c
SRCS		= ${patsubst %, ${SRCS_DIR}%, ${SRCS_FILES}}

BONUS_DIR	= ./
BONUS_FILES	= 
BONUS		= ${patsubst %, ${BONUS_DIR}%, ${BONUS_FILES}}

LIBFT		= ./libft/
MAKELIB		= ${MAKE} -C ${LIBFT}

OBJS		= ${SRCS:.c=.o}
OBJSB		= ${BONUS:.c=.o}

NAME		= minishell
NAMEB		= minishell_bonus

CC			= gcc
AR			= ar rcs
CP			= cp -f
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

HEADS		= -I. -I${LIBFT} -I${HOME}/.brew/Cellar/readline/8.1.1/include/

LIBS		= -L${HOME}/.brew/Cellar/readline/8.1.1/lib/ -lreadline -lhistory

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${HEADS} -g

all:		${NAME}

${NAME}:	${OBJS}
			@tput setaf 2
			${MAKELIB} all
			${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBFT}/libft.a ${LIBS} -g -fsanitize=address
			@tput setaf 1

${NAMEB}:	${OBJSB}
			${MAKELIB} all
			${CC} ${CFLAGS} -o ${NAMEB} ${OBJSB} ${LIBFT}/libft.a ${LIBS}

bonus:		${NAMEB}

clean:
			@tput setaf 1
			${RM} ${OBJS} ${OBJSB}
			${MAKELIB} clean
			@tput setaf 2

fclean:		clean
			@tput setaf 1
			${RM} ${NAME} ${NAMEB}
			${MAKELIB} fclean
			@tput setaf 2

re:			fclean all

.PHONY:		all bonus clean fclean re
