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
SRCS       = src/banquet.c src/ft_atoi.c src/log_status.c src/chrono.c src/set_table.c\
			 src/argparser.c src/killer.c src/philo.c src/routines.c src/control.c
OBJS       = ${SRCS:src/%.c=$(OBJ_DIR)/%.o}
INCS 	   = inc/
NAME       = philo
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
