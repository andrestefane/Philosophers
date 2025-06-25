# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/16 18:36:39 by astefane          #+#    #+#              #
#    Updated: 2025/06/25 14:55:49 by astefane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3

SRCS := \
	main.c \
	parse.c \
	utils_parse.c \
	init_struct.c \
	ft_message_error.c \
	utils_main.c \
	philo_routine.c \
	monitor.c \

OBJ_DIR := obj
OBJS := $(SRCS:.c=.o)
OBJ_FILES := $(addprefix $(OBJ_DIR)/, $(OBJS))

INCLUDES := -I. -I includes

TOTAL_FILES := $(words $(SRCS))
COUNT := 0
PERCENT := 0

all: $(NAME)

$(NAME): $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)
	@echo "\033[1;34mLink complete -> $(NAME)\033[0m"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@if [ "$(COUNT)" -eq "0" ]; then \
		echo "\033[1;33mCompiling philo...\033[0m"; \
	fi
	$(eval COUNT := $(shell echo $$(( $(COUNT) + 1 ))))
	$(eval PERCENT := $(shell echo $$(( $(COUNT) * 100 / $(TOTAL_FILES) ))))
	@echo "\033[1;32m[$(PERCENT)%]Building C object $@\033[0m"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[1;31mObject files removed.\033[0m"


fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;31mProgramm removed.\033[0m"


re: fclean all

.PHONY: all clean fclean re
