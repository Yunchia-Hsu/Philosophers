NAME := philo

CC := cc

# -g -fsanitize=thread
CFLAGS := -Wall -Werror -Wextra 


BLUE := \033[0;34m
YELLOW := \033[0;33m
RESET := \033[0m

# Directories
OBJS_DIR := objs/

SRCS := main.c philo_utils.c init.c philo_routine.c monitoring.c printing.c clean_all.c philo_checks.c valid_input.c

# Object files with path
OBJS := $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

all: $(NAME)

# Create the executable
$(NAME): $(OBJS_DIR) $(OBJS)
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS)
	@echo "$(BLUE)Built $@$(RESET)"

# Create the object directory
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

# Compile source files to object files
$(OBJS_DIR)%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ 
	@echo "$(BLUE)Compiled $< to $@$(RESET)"

clean:
	@rm -fr $(OBJS_DIR)
	@echo "$(BLUE)$(OBJS_DIR) directory and object files were removed$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(BLUE)Removed $(NAME)$(RESET)"

re: fclean all
