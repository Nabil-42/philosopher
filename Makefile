# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabil <nabil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 16:08:48 by nabil             #+#    #+#              #
#    Updated: 2024/05/09 17:33:16 by nabil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES

NAME        = philo
NAME_BONUS  = philo_bonus
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
INCLUDES    = -I$(LIBFT_DIR)
RM          = rm -rf

SRC_PHILO       = src/philo.c
SRC_PHILO_BONUS = src/philo_bonus.c

OBJ_DIR     = obj
OBJ_PHILO       = $(addprefix $(OBJ_DIR)/, $(SRC_PHILO:.c=.o))
OBJ_PHILO_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_PHILO_BONUS:.c=.o))

# **************************************************************************** #
# RULES

all: $(NAME) $(NAME_BONUS)

$(NAME): $(OBJ_PHILO) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_PHILO) $(LIBFT) -o $(NAME)
	@echo "Compilation de $(NAME) réussie."

$(NAME_BONUS): $(OBJ_PHILO_BONUS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ_PHILO_BONUS) $(LIBFT) -o $(NAME_BONUS)
	@echo "Compilation de $(NAME_BONUS) réussie."

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@$(RM) $(NAME) $(NAME_B)
