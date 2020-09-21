# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fjimenez <fjimenez@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/18 08:07:14 by fjimenez          #+#    #+#              #
#    Updated: 2020/09/17 20:35:11 by fjimenez         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CFILES = $(addsuffix .c, $(SRCS))

OFILES = $(addsuffix .o, $(SRCS))

BONUSFILES = $(addsuffix .c, $(SRCBONUS))

BONUSOBJ = $(addsuffix .o, $(SRCBONUS))

INC = libft.h

SRCS =	ft_calloc ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii \
		ft_isdigit ft_isprint ft_memccpy ft_memchr ft_memcmp \
		ft_memcpy ft_memmove ft_memset ft_strchr ft_strdup \
		ft_strlcat ft_strlcpy ft_strlen ft_strncmp ft_strnstr \
		ft_strrchr ft_tolower ft_toupper ft_substr ft_strjoin \
		ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_strtrim \
		ft_itoa ft_putnbr_fd ft_strmapi ft_split

SRCBONUS = ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus ft_lstlast_bonus \
			ft_lstadd_back_bonus ft_lstdelone_bonus ft_lstclear_bonus \
			ft_lstiter_bonus ft_lstmap_bonus

RED = \033[1;31m
GREEN = \033[1;32m
BLUE = \033[1;34m
RESET = \033[0m
PURPLE = \033[0;35m
YELLOW = \033[0;33m

.PHONY: re clean fclean all

$(VERBOSE).SILENT:

all: $(NAME) execute

$(NAME): $(OFILES) $(BONUSOBJ) $(HEADER)

execute :
	@$(CC) $(CFLAGS) -c $(CFILES) $(BONUSSRC)
	@ar -rcs $(NAME) $(OFILES) $(BONUSOBJ) $(HEADER)
	@ranlib $(NAME)

clean:
	@rm -f $(OFILES) $(BONUSOBJ)
	@echo "$(RED)(LIBFT)\t$(PURPLE)====REMOVED====$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)(LIBFT)\t$(RED)====REMOVED====$(RESET)"

re:	fclean all