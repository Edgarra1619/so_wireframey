NAME = FdF
SRCS = main.c colors.c my_math.c render.c map.c hooks.c vector.c
SRCDIR = ./srcs/
OBJDIR = ./objs/
MINILIBX = ~/42libraries/minilibx-linux/
TESTARGS = 
CC = cc
INCFLAGS = -I $(MINILIBX) -I ./includes/
CFLAGS = -Wall -Wextra -Werror -g -D WINDOW_WIDTH=960 -D WINDOW_HEIGHT=720

OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	make -C $(MINILIBX) clean

re: clean all

$(NAME): $(OBJS) $(MINILIBX)libmlx_Linux.a 
	$(CC) $(CFLAGS) $(OBJS) $(MINILIBX)libmlx_Linux.a $(INCFLAGS) -o $@\
		-lXext -lX11 -lm -lbsd 

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -c -o $@

$(MINILIBX)libmlx.a:
	make -C $(MINILIBX)

$(MINILIBX)libmlx_Linux.a:
	make -C $(MINILIBX)


test: $(NAME) 
	./$(NAME) $(TESTARGS)

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME) $(TESTARGS)
