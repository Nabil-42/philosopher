# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nabil <nabil@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/13 16:08:48 by nabil             #+#    #+#              #
#    Updated: 2024/07/16 18:56:05 by nabil            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# VARIABLES
# -fsanitize=thread
NAME        = philo
NAME_BONUS  = philo_bonus
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g -O0 
INCLUDES    = -Isrc
RM          = rm -rf

SRC_PHILO       = src/main.c src/outils_lib.c src/verif.c src/if_six_arg.c
SRC_PHILO_BONUS = src/philo_bonus.c

OBJ_DIR     = obj
OBJ_PHILO       = $(addprefix $(OBJ_DIR)/, $(SRC_PHILO:.c=.o))
OBJ_PHILO_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_PHILO_BONUS:.c=.o))

# COLORS
CYAN        = \033[0;36m
GREEN       = \033[0;32m
END_COLOR   = \033[0m

# **************************************************************************** #
# RULES

all: $(NAME)

$(NAME): $(OBJ_PHILO)
	@$(CC) $(CFLAGS) $(OBJ_PHILO) -o $(NAME)
	@echo "$(GREEN)[Compilation]$(END_COLOR) $(NAME) compilé avec succès.                        "

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@printf "$(GREEN)[Compilation]$(END_COLOR) Compilation de $(CYAN)$<$(END_COLOR)...\r"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)[Nettoyage]$(END_COLOR) Dossier des objets supprimé."

fclean: clean
	@$(RM) $(NAME) $(NAME_BONUS)
	@echo "$(GREEN)[Nettoyage]$(END_COLOR) Exécutable(s) supprimé(s)."

re: fclean all

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_PHILO_BONUS)
	@$(CC) $(CFLAGS) $(OBJ_PHILO_BONUS) -o $(NAME_BONUS)
	@echo "$(GREEN)[Compilation]$(END_COLOR) $(NAME_BONUS) compilé avec succès."

