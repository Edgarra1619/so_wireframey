NAME = FdF
SRCS = main.c
SRCDIR = ./srcs/
OBJDIR = ./objs/
MINILIBX = ~/42libraries/minilibx-linux/ 
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCFLAGS = -lXext -lX11 -lm -lbsd -I $(MINILIBX)

OBJS = $(patsubst %.c, $(OBJDIR)%.o, $(SRCS))

all: $(NAME)

clean:
	$(RM) -r $(OBJDIR)
	make -C $(MINILIBX) clean

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(NAME): $(OBJS) $(MINILIBX)libmlx_Linux.a 
	$(CC) $(CFLAGS) $(OBJS) $(MINILIBX)libmlx_Linux.a $(INCFLAGS) -o $@

$(OBJS): $(OBJDIR)%.o: $(SRCDIR)%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCFLAGS) $^ -c -o $@

$(MINILIBX)libmlx.a:
	make -C $(MINILIBX)

$(MINILIBX)libmlx_Linux.a:
	make -C $(MINILIBX)
