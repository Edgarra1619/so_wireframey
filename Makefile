NAME = FdF
<<<<<<< HEAD
SRCS = main.c draw.c
=======
SRCS = main.c colors.c my_math.c render.c
>>>>>>> 60ab408c2b622178dc6e86c6cd1bd09376ee978c
SRCDIR = ./srcs/
OBJDIR = ./objs/
MINILIBX = ~/42libraries/minilibx-linux/
TESTARGS = 
CC = cc
<<<<<<< HEAD
CFLAGS = -Wall -Wextra -Werror -g
=======
CFLAGS = -Wall -Wextra -g
>>>>>>> 60ab408c2b622178dc6e86c6cd1bd09376ee978c
INCFLAGS = -lXext -lX11 -lm -lbsd -I $(MINILIBX) -I ./includes/

OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)
	make -C $(MINILIBX) clean

re: clean all

$(NAME): $(OBJS) $(MINILIBX)libmlx_Linux.a 
	$(CC) $(CFLAGS) $(OBJS) $(MINILIBX)libmlx_Linux.a $(INCFLAGS) -o $@

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
