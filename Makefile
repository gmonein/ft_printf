# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/08 06:09:56 by gmonein           #+#    #+#              #
#    Updated: 2018/05/02 05:12:37 by gmonein          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libftprintf.a
DFLAGS = #-fsanitize=address -g3
FLAGS = -Wall -Wextra $(DFLAGS)#-Werror
LIBFT = libft
DIR_S = srcs
DIR_O = obj
HEADER = includes
SOURCES = printf.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@make -C $(LIBFT)
	ar rc $(NAME) $(OBJS) $(LIBFT)/$(LIBFT).a
	ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p obj
	$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

norme:
	norminette ./libft/
	@echo
	norminette ./$(HEADER)/
	@echo
	norminette ./$(DIR_S)/

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)
	@make clean -C $(LIBFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT)

test: $(NAME)
	make -C ../printf-unit-test/
	../printf-unit-test/run_test

re: fclean all

.PHONY: fclean re norme all clean
