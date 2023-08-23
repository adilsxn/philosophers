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


SRCS       = mandatory/src/banquet.c mandatory/src/utils.c            \
						 mandatory/src/set_table.c mandatory/src/actions.c        \
						 mandatory/src/argparser.c mandatory/src/philo.c          \
						 mandatory/src/routines.c
B_SRC      = bonus/src/set_table_bonus.c bonus/src/utils_bonus.c       \
             bonus/src/philo_bonus.c bonus/src/argparser_bonus.c       \
						 bonus/src/banquet_bonus.c bonus/src/actions_bonus.c       

OBJS       = ${SRCS:mandatory/src/%.c=$(OBJ_DIR)/%.o}
B_OBJS     = ${B_SRC:bonus/src/%.c=$(B_OBJ_DIR)/%.o}
BUILD_DIR  = ./build
OBJ_DIR    = ${BUILD_DIR}/obj
B_OBJ_DIR  = ${BUILD_DIR}/b_obj
INCS 			 = ./mandatory/inc/
B_INCS     = ./bonus/inc/
NAME       = philo
B_NAME     = philo_bonus
CC         = cc
CFLAGS     = -g -Wall -Wextra -Werror
LDFLAGS 	 = -lpthread
RM         = rm -rf

all: ${NAME}

$(OBJ_DIR)/%.o: mandatory/src/%.c | DIRECTORIES
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) ${LDFLAGS}

${NAME}: ${OBJS}
	@echo "Compiling philo"
	@${CC} ${CFLAGS}  $^ -o $@  -I ${INCS} ${LDFLAGS}
	@mv ${NAME} ${BUILD_DIR}/
	@echo "philo created"

$(B_OBJ_DIR)/%.o: bonus/src/%.c | DIRECTORIES
	@$(CC) $(CFLAGS) -I $(INCS) -c $< -o $@ -I $(INCS) ${LDFLAGS}

bonus: ${B_OBJS}
	@echo "Compiling philo_bonus"
	@${CC} ${CFLAGS}  $^ -o ${B_NAME} -I ${INCS} ${LDFLAGS}
	@mv ${B_NAME} ${BUILD_DIR}/
	@echo "philo_bonus created"

DIRECTORIES:
	@mkdir -p ${BUILD_DIR}
	@mkdir -p ${OBJ_DIR} ${B_OBJ_DIR}

clean:
	@${RM} ${OBJS} ${B_OBJS}

fclean: clean
	@${RM} ${BUILD_DIR}
	@echo "philo deleted"

re: fclean all

norm:
	norminette -R CheckForbiddenSourceHeader ${SRCS}
	norminette -R CheckDefine ${INCS}

.PHONY: all re clean fclean bonus
