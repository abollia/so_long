#******************************************************************************#

#--------------------------\\\\\___VARIABLES___/////---------------------------#

MAKEFLAGS	+= --no-print-directory

NAME		=	so_long

CC			=	cc
FLAGS		=	-Wall -Wextra -Werror -g3 -I${INCLUDE}
MLXFLAGS	=	-ldl -lglfw -pthread -lm

OBJ_DIR		=	obj
SRC_DIR		=	src

#---------------------------\\\\\___SOURCES___/////----------------------------#

SRC			=	${MAIN} ${UTILS}

MAIN		=	./src/sl_main.c

UTILS		=	./src/sl_utils.c \
				./src/sl_input.c \
				./src/sl_map_parsing.c \
				./src/sl_map_respath.c \
				./src/sl_display.c \
				./src/sl_game.c

LIBFT		=	./libft/libft.a
MLX			=	./MLX42/build/libmlx42.a
INCLUDE		=	./inc/

OBJ			=	$(patsubst %.c,${OBJ_DIR}/%.o,${SRC})

#----------------------------\\\\\___RULES___/////-----------------------------#

all:			${NAME}

${OBJ_DIR}/%.o: %.c | ${OBJ_DIR}
				@mkdir -p $(dir $@)
				@${CC} ${FLAGS} -c $< -o $@

${OBJ_DIR}:
				@mkdir -p ${OBJ_DIR}

${LIBFT}:
				@echo "📡 Pulling libft..."
				@git clone https://github.com/abollia/libft.git > /dev/null 2>&1;
				@make -C libft

vpath %.c . ${SRC_DIR}

${MLX}:
				@echo "📡 Pulling MLX..."
				@git clone https://github.com/codam-coding-college/MLX42.git > /dev/null 2>&1; \
				cd ./MLX42 && \
				cmake -B build > /dev/null 2>&1 && \
				cmake --build build -j4 > /dev/null 2>&1
				@echo "✅🦾 MLX ready for use."

${NAME}:		${MLX} ${LIBFT} ${OBJ}
				@echo "🧠⚡ Compiling ${NAME}..."
				@${CC} ${FLAGS} ${OBJ} ${MLX} ${MLXFLAGS} ${LIBFT} -o ${NAME}
				@echo "✅🦾 ${NAME} is ready!"

clean:
				@echo "🚮 Removing project files..."
				@rm -rf MLX42
				@rm -rf ${OBJ_DIR}
				@make clean -C ./libft

fclean:			clean
				@echo "🚮 Removing project..."
				@rm -f ${NAME}
				@rm -rf libft
				@echo "❌ ${NAME} has been removed."

re:				fclean all

.PHONY:			all clean fclean re

#******************************************************************************#