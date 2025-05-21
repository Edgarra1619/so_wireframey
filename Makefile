NAME = FdF
SRCS = main.c colors.c my_math.c render.c map.c hooks.c vector.c gifparse.c gifimg_utils.c
SRCDIR = ./srcs/
OBJDIR = ./objs/
LIBFT = ./libft/
MINILIBX = ~/42libraries/minilibx-linux/
TESTARGS = ./maps/nerd.gif
CC = clang
INCFLAGS = -I $(MINILIBX) -I ./includes/ -I $(LIBFT)
CFLAGS = -Wall -Wextra -Werror -gdwarf-4 -O0 -D WINDOW_WIDTH=960 -D WINDOW_HEIGHT=720
OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	make -C $(MINILIBX) clean

re: clean all

$(NAME): $(OBJS) $(MINILIBX)libmlx_Linux.a $(LIBFT)libft.a
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT)libft.a $(MINILIBX)libmlx_Linux.a $(INCFLAGS) -o $@\
		-lXext -lX11 -lm -lbsd 

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -c -o $@

$(LIBFT)libft.a:
	make -C $(LIBFT)

$(MINILIBX)libmlx.a $(MINILIBX)libmlx_Linux.a:
	make -C $(MINILIBX)

test: $(NAME) 
	./$(NAME) $(TESTARGS)

gprof: $(NAME)
	./$(NAME) $(TESTARGS)
	rm gprof-output -f
	gprof $(NAME) > gprof-output

valgrind: $(NAME)
	valgrind --track-origins=yes --leak-check=full ./$(NAME) $(TESTARGS)

gdb: $(NAME)
	gdbtui --args $(NAME) $(TESTARGS)
