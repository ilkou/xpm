# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oouklich <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/18 14:32:27 by oouklich          #+#    #+#              #
#    Updated: 2019/08/16 13:34:50 by oouklich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = loadxpm

SRC = main.c

OBJ = $(SRC:.c=.o)

OK_COLOR=\x1b[32;01m
NO_COLOR=\x1b[0m
BUILD_PRINT = $(OK_COLOR)loadxpm successfully compiles$(NO_COLOR)
OK_STRING=$(OK_COLOR)[OK]$(NO_COLOR)

ifeq ($(shell uname), Darwin)
$(info MacOs detected)
MLX = -I ./minilibx_macos -L ./minilibx_macos -lmlx -framework OpenGL -framework AppKit
else
$(info $(shell uname) detected)
MLX = -lm -lmlx -lXext -lX11
endif

CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/ -lft
THREAD = -lpthread
MYFLAG =  $(MLX) -L $(LIBFT) $(THREAD)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@gcc $(CFLAGS) -o $(NAME) $^ $(MYFLAG)
	@echo "$(BUILD_PRINT)"

%.o: %.c
	@echo "`gcc -I ./minilibx_macos  -o $@ -c $<`$< => $@ $(OK_STRING)"

clean:
	@echo "$(OK_COLOR)Deleting objects...$(NO_COLOR)"
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@echo "$(OK_COLOR)Deleting loadxpm...$(NO_COLOR)"
	@make fclean -C libft
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
