NAME = libft.a
FLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS = 	../ft_printf/ft_printf.c\
		../ft_printf/ft_print_basics.c\
		../ft_printf/ft_print_u.c\
		../ft_printf/ft_print_x.c\

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

.c.o:
	@cc $(FLAGS) -c -o $@ $<

all: $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re