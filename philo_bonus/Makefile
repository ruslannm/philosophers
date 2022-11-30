NAME = philo_bonus

CLANG = gcc
CLANG_FLAGS = -Wall -Wextra -Werror -pthread

SRC = ft_main.c ft_fork.c ft_parser.c ft_philosopher.c ft_process.c \
	ft_state.c ft_thread.c ft_time.c ft_table.c
OBJ = $(SRC:%.c=%.o)
DEP = $(OBJ:%.o=%.d)

$(NAME) : $(OBJ)
	$(CLANG) $(CLANG_FLAGS) $^ -o $@

-include $(DEP)

%.o : %.c
	$(CLANG) $(CLANG_FLAGS) -MMD -c $< -o $@

.PHONY: all re clean fclean

all : $(NAME)

clean :
	rm -f $(OBJ) $(DEP)
fclean: clean
	rm -f $(NAME)

re: fclean all
