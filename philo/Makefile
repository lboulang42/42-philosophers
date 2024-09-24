# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 13:26:12 by lboulang          #+#    #+#              #
#    Updated: 2023/10/12 20:03:44 by lboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME
NAME = 			philo
#SOURCES
SRCS_NAMES 	=	main.c\
				initialization.c\
				parsing.c\
				print.c\
				routine_actions.c\
				routine.c\
				clean.c\
				time.c\

DIR_SRCS	=	srcs
DIR_OBJS	=	objs
OBJS_NAMES	=	${SRCS_NAMES:.c=.o}
DEPS		=	${SRCS_NAMES:.c=.d}
SRCS		=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))
OBJS		=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))
INC			= 	-Iincludes
LIB			= 	-pthread
CDFLAGS 	= 	-MMD -MP
CFLAGS		=	-g3 -Wall -Werror -Wextra -pthread
all: ${NAME}

$(NAME): $(DIR_OBJS) $(OBJS)
	$(CC) $(CFLAGS) ${INC} $(OBJS) $(LIB) -o $(NAME)
	@echo "\033[31;5mPhilosopher\033[0m"

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) $(CFLAGS) $(CDFLAGS) $(INC) -c $< -o $@ 

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

clean : 
	rm -rf ${DIR_OBJS}
	@echo "MANDATORY CLEANED 🚮\n"
	
fclean : clean
	rm -rf ${NAME}

re : fclean all

.PHONY : all clean fclean re leaks