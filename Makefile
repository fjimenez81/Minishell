# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fernando <fernando@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/18 21:02:40 by fernando          #+#    #+#              #
#    Updated: 2020/04/20 20:28:21 by fernando         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = minishell.h

CFILES = $(addsuffix .c, $(SRC))

OFILES = $(addsuffix .o, $(SRC))

SRC =	main \
		ft_utils \
		ft_utils2 \
		ft_arg_echo \
		ft_arg_cd \
		ft_arg_env \
		ft_arg_export \
		ft_arg_unset \
		ft_str_tok \
		ft_init_env \

SRCGNL = gnl/get_next_line.c gnl/get_next_line_utils.c

LIBFT = libft/libft.a

CC = gcc -Wall -Wextra -Werror

RM = rm -rf

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m
PURPLE = \033[0;35m
YELLOW = \033[0;33m

all: $(NAME)

$(NAME):
	@make -C libft/
	@$(CC) $(LIBFT) ${SRCGNL} $(CFILES) -o $(NAME)
	@echo "$(RED)(MINISHELL)$(BLUE)====CREATED====$(RESET)"

clean:
	@$(RM) $(OFILES)
	@make -C libft/ clean

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)(MINISHELL)$(YELLOW)====REMOVED====$(RESET)"

re : fclean all