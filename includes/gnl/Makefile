NAME = gnl

RM = rm -f
CC = cc
AR = ar rcs
CC_FLAGS=-Wall -Wextra -Werror
DIR_SRCS = source/
DIR_INCLUDES = includes/

GET_SRCS = $(shell find $(DIR_SRCS))

FILTER_SRCS = $(filter %.c, $(GET_SRCS))

OBJS = $(FILTER_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $@ -I $(DIR_INCLUDES)

re: fclean all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
