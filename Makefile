
NAME := philo

CC := cc

#-fsanitize=thread
CFLAGS := =Wall -Werror -Wextra -fsanitize=thread

YELLOW := \033[0;33m
RESET := \033[0m

#dericetories
OBJS_DIR := objs/

SRCS := main.c philo_utils.c init.c philo_routine.c monitoring.c free.c printing.c

#object file with path
OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

(NAME): $(OBJS_DIR) $(OBJS)
	@cc -o $(NAME) $(OBJS)
	@echo "$(YELLOW)Built $@$(RESET)"

clean:
		@rm -fr $(OBJS_DIR)
		@echo "$(YELLOW) $(OBJS_DIR) directory and object files were removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "Removed $(RESET)"

re: fclean all