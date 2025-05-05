NAME = cub3D

LIBFT_A = includes/libft/libft.a
RM = rm -rf
COMPILER = cc -Wall -Wextra -Werror -I ./includes
MINILIBX_ARGS = -lXext -lX11 -lm
MINILIBX_A = minilibx/libmlx.a

DIR_OBJS = builds/
DIR_SRCS = srcs/
DIR_INCLUDES = includes/
MAPS_DIR = $(DIR_SRCS)/maps/
GET_SRCS = $(shell find $(DIR_SRCS))
ALL_MAPS = $(filter %.cub, $(shell find $(MAPS_DIR)))

PRE-FILTER_SRCS = $(filter %.c, $(GET_SRCS))

FILTER_SRCS = $(filter-out %testing.c, $(PRE-FILTER_SRCS))

OBJS = $(FILTER_SRCS:%.c=$(DIR_OBJS)/%.o)

MAP = map_default.cub

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
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) $(MAPS_DIR)$(MAP)

compile: all
	@echo "map is $(MAP)"
	@./$(NAME) $(MAPS_DIR)$(MAP)

echo-maps:
	@for file in $(ALL_MAPS); do\
		echo "Validando $$file";\
		if ./$(NAME) $$file | grep -q "MAJOR SCOPE";\
		then \
			echo "O MAPA FOI VALIDADO"; \
		else \
			echo "O MAPA NÃO FOI VALIDADO"; \
		fi \
		done

assert-map:
	@echo "map is $(MAP)"
	@if ./$(NAME) $(MAPS_DIR)$(MAP) | grep -q "MAJOR SCOPE";\
		then \
			echo "O MAPA FOI VALIDADO"; \
		else \
			echo "O MAPA NÃO FOI VALIDADO"; \
		fi \

testing:
	$(COMPILER) -c ./srcs/testing/testing.c -o $(DIR_OBJS)/testing.o
	$(COMPILER) $(DIR_OBJS)/testing.o $(MINILIBX_A) $(MINILIBX_ARGS) $(LIBFT_A) -o testing_$(NAME)
	./testing_$(NAME)
clean:
	$(RM) $(DIR_OBJS)
	cd includes/libft && make clean && cd ../..
	cd minilibx/ && make clean && cd ..

fclean: clean
	$(RM) $(NAME) $(DIR_OBJS) $(LIBFT_A) $(MINILIBX_A)

re: fclean all

