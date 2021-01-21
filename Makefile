# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjimenez <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/18 21:02:40 by fernando          #+#    #+#              #
#    Updated: 2021/01/21 07:25:33 by fjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

INC = minishell.h

SRC =	main \
		ft_utils \
		ft_utils2 \
		ft_arg_cd \
		ft_arg_env \
		ft_arg_export \
		ft_arg_unset \
		ft_arg_echo \
		ft_init_env \
		ft_split_cmd \
		ft_realloc_str \
		ft_realloc_str_aux \
		ft_redirections \
		ft_exp_print \
		ft_check_export \
		ft_realloc_var \
		ft_check_pipes \
		ft_loop_pipes \
		ft_arg_exe \
		ft_arg_exit \
		ft_pipes_utils \
		ft_check_syntax \
		ft_only_path \

CFILES = $(addsuffix .c, $(SRC))

OFILES = $(addsuffix .o, $(SRC))

LIBFT = libft/libft.a
M_LIBFT = make -C libft/

CC = gcc -Wall -Wextra -Werror 

RM = rm -rf

#$(VERBOSE).SILENT:

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m
PURPLE = \033[0;35m
YELLOW = \033[0;33m

all: $(NAME) 

$(NAME): $(OFILES)
	@$(M_LIBFT)
	@$(CC) $(CFILES) $(LIBFT) -o $(NAME) 
	@echo "$(RED)(MINISHELL)$(BLUE)====CREATED====$(RESET)"
	

clean:
	@$(RM) $(OFILES)
	@make -C libft/ fclean

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)(MINISHELL)$(YELLOW)====REMOVED====$(RESET)"

re : fclean all