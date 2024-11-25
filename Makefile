NAME = cub3D

RM = rm -rf
COMPILER = cc -Wall -Wextra -Werror

DIR_OBJS = builds/
DIR_SRCS = srcs/
DIR_INCLUDES = includes/
GNL_A = includes/gnl/gnl.a
LIBFT_A = includes/libft/libft.a

GET_SRCS = $(shell find $(DIR_SRCS))

PRE-FILTER_SRCS = $(filter %.c, $(GET_SRCS))

FILTER_SRCS = $(filter-out %testing.c, $(PRE-FILTER_SRCS))

OBJS = $(FILTER_SRCS:%.c=$(DIR_OBJS)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(GNL_A) $(DIR_OBJS)
	$(COMPILER) $(OBJS) $(LIBFT_A) $(GNL_A) -o $(NAME)

$(DIR_OBJS):
	mkdir builds

$(LIBFT_A):
	cd includes/libft && make && cd ../..

$(GNL_A):
	cd includes/gnl && make && cd ../..

$(DIR_OBJS)/%.o : %.c
	mkdir -p $(dir $@)
	$(COMPILER) -c $< -o $@

val: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

clean:
	$(RM) $(DIR_OBJS)
	cd includes/libft && make clean && cd ../..

fclean: clean
	$(RM) $(NAME) $(DIR_OBJS) $(LIBFT_A) $(GNL_A)

re: fclean all
