NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g -pthread 


CFILES = main.c  \
	checkargs.c  \
	init.c       \
	simulator.c  \
	simulation.c \
	time_utils.c \
	sim_utils.c  \
	utils.c

OBJECTS = $(CFILES:.c=.o)

all: $(NAME)

%.o : %.c
	@echo $(Y)Compiling [$<]...$(X)
	@$(CC) $(CFLAGS) -c -o $@ $<



$(NAME): $(OBJECTS)
	@echo $(Y)Compiling [$(CFILES)]...$(X)
	@echo $(G)Finished [$(CFILES)]$(X)
	@echo
	@echo $(Y)Compiling [$(NAME)]...$(X)
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)

clean:
#	@make -C $(LIBFT_PATH) clean
#	@make -C $(PRINTF_PATH) clean
	@rm -f $(OBJECTS)
	@echo Removed [$(OBJECTS)]$(X)

fclean: clean
#	@make -C $(LIBFT_PATH) fclean
#	@make -C $(PRINTF_PATH) fclean
	@rm -f $(NAME)
	@echo Removed [$(NAME)]$(X)

re: fclean all


.PHONY: all clean fclean re norm