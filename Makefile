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
FLAGS = -Wall -Wextra -Werror
DIR_S = srcs
DIR_O = obj
HEADER = includes
SOURCES = \
  buf.c \
  char_alloc.c \
  get_modifier.c \
  itoa.c \
  misc.c \
  modifier.c \
  operator_one.c \
  operator_three.c \
  operator_two.c \
  pas_main.c \
  printf.c \
  libft.c \
  wchar.c

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJS) includes/ft_printf.h includes/ft_printf_struct.h
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p obj
	$(CC) $(FLAGS) -I $(HEADER) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@rm -rf $(DIR_O)

fclean: clean
	@rm -f $(NAME)

test: $(NAME)
	make -C ../printf-unit-test/
	../printf-unit-test/run_test

re: fclean all

.PHONY: fclean re norme all clean
