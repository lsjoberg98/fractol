# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsjoberg <lsjoberg@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/21 15:56:04 by jaleman           #+#    #+#              #
#    Updated: 2020/06/01 16:05:45 by lsjoberg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program
NAME = fractol

# Compiling flags
FLAGS = -Wall -Wextra -Werror -g

# Folders
SRC_DIR = ./srcs/
OBJ_DIR = ./obj/
INC_DIR = ./includes/
LIBFT_DIR = ./libft/
MINLBX_DIR = ./minilibx/

# Source files and object files
SRC_FILES = main.c draw.c fractals.c control.c
OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MINLBX = $(addprefix $(MINLBX_DIR), libmlx.a)

# Libft and Minilibx linkers
LNK  = -L $(LIBFT_DIR) -lft -L $(MINLBX_DIR) \
		-Ofast -lmlx -framework OpenGL -framework AppKit

# all rule
all: obj $(LIBFT) $(MINLBX) $(NAME)

obj:
	@mkdir -p $(OBJ_DIR)
$(OBJ_DIR)%.o:$(SRC_DIR)%.c
	@gcc $(FLAGS) -I $(MINLBX_DIR) -I $(LIBFT_DIR) -I $(INC_DIR) -o $@ -c $<
$(LIBFT):
	@make -C $(LIBFT_DIR)
$(MINLBX):
	@make -C $(MINLBX_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo "(ﾉ◕ヮ◕)ﾉ*:・ﾟ✧ Compiling... Wait a sec."
	@gcc $(OBJ) $(LNK) -lm -o $(NAME)
	@echo "(•̀ᴗ•́)و $(NAME) generated!"

# clean rule
clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MINLBX_DIR) clean
	@echo "¯\_(ツ)_/¯ Objects removed!"

# fclean rule
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "(╯°□°）╯︵ ┻━┻ $(NAME) removed!"

# re rule
re: fclean all

# phony
.PHONY: all clean fclean re
