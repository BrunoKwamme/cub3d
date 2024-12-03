NAME = cub3D

RM = rm -rf
COMPILER = cc -Wall -Wextra -Werror
MINILIBX_ARGS = -lXext -lX11 -lm

DIR_OBJS = builds/
DIR_SRCS = srcs/
DIR_INCLUDES = includes/
LIBFT_A = includes/libft/libft.a
MINILIBX_A = minilibx/libmlx.a

GET_SRCS = $(shell find $(DIR_SRCS))

PRE-FILTER_SRCS = $(filter %.c, $(GET_SRCS))

FILTER_SRCS = $(filter-out %testing.c, $(PRE-FILTER_SRCS))

OBJS = $(FILTER_SRCS:%.c=$(DIR_OBJS)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(MINILIBX_A) $(LIBFT_A) $(DIR_OBJS)
	$(COMPILER) $(OBJS) $(MINILIBX_A) $(MINILIBX_ARGS) $(LIBFT_A) -o $(NAME)

$(DIR_OBJS):
	mkdir builds

$(LIBFT_A):
	cd includes/libft && make && cd ../..

$(MINILIBX_A):
	cd minilibx && make && cd ..

$(DIR_OBJS)/%.o : %.c
	mkdir -p $(dir $@)
	$(COMPILER) -c $< -o $@

val: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(MAP)

clean:
	$(RM) $(DIR_OBJS)
	cd includes/libft && make clean && cd ../..
	cd minilibx/ && make clean && cd ..

fclean: clean
	$(RM) $(NAME) $(DIR_OBJS) $(LIBFT_A) $(MINILIBX_A)

re: fclean all
