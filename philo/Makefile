# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acuva-nu <acuva-nustudent.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/29 12:35:24 by acuva-nu          #+#    #+#              #
#    Updated: 2023/02/25 16:34:52 by acuva-nu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
OBJ_DIR    = ./obj
SRCS       = src/ffree.c src/fmemset.c src/fcalloc.c src/fatoi.c  \
		     src/exit.c  src/log.c  src/timer.c src/forks.c       \
			 src/actions.c src/threads.c  src/philo.c
OBJS       = ${SRCS:src/%.c=$(OBJ_DIR)/%.o}
INCS 	   = inc/
NAME       = philo_bonus
CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror
LDFLAGS    = -lpthread
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS)

${NAME}: ${OBJS}
	@echo "Compiling philo"
	@${CC} ${CFLAGS}  $^ -o $@  -I ${INCS} ${LDFLAGS}
	@echo "philo created"
$(OBJ_DIR):
	@mkdir -p ${OBJ_DIR}

clean:
	@${RM} ${OBJ_DIR}

fclean: clean
	@${RM} ${NAME}
	@echo "philo deleted"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean