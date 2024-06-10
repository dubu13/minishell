# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 15:40:08 by dhasan            #+#    #+#              #
#    Updated: 2024/06/10 23:24:19 by dhasan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -I/inc
# REMOVE WILDCARD LATER!!
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RL_FLAGS = -lreadline
INCLUDE = -L $(LIBFT_PATH) -lft

LIBFT_PATH = ./lib
LIBFT = $(LIBFT_PATH)/libft.a

BINDIR = bin

SRCS = $(wildcard *.c) $(wildcard parsing/*.c) $(wildcard builtins/*.c)
OBJS = $(SRCS:%.c=$(BINDIR)/%.o)

all: $(NAME)

.SILENT:

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJS) $(INCLUDE) $(RL_FLAGS)
	echo $(GREEN)"Building $(NAME)"$(DEFAULT);

$(LIBFT):
	make -C $(LIBFT_PATH)

$(BINDIR):
	echo $(GREEN)"Creating $(BINDIR) directory"$(DEFAULT);
	mkdir -p $(BINDIR)

$(BINDIR)/%.o: %.c | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

submodule:
	git submodule update --init --recursive

clean:
	make clean -C $(LIBFT_PATH)
	rm -f $(BINDIR)/*.o
	echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

fclean: clean
	rm -f $(NAME)
	rm -rf $(BINDIR)
	make fclean -C $(LIBFT_PATH)
	echo $(RED)"Removing $(NAME)"$(DEFAULT);

re: fclean all
	echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colours
DEFAULT = "\033[39m"
GREEN = "\033[32m"
RED = "\033[31m"
