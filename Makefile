# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 15:40:08 by dhasan            #+#    #+#              #
#    Updated: 2024/07/10 12:20:13 by dhasan           ###   ########.fr        #
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
PARSEDIR = $(BINDIR)/parsing
BUILDDIR = $(BINDIR)/builtins
EXECDIR = $(BINDIR)/exec
MAINDIR = $(BINDIR)/main

SRCS = $(wildcard *.c) $(wildcard parsing/*.c) $(wildcard builtins/*.c) $(wildcard exec/*.c) $(wildcard main/*.c)
OBJS = $(SRCS:%.c=$(BINDIR)/%.o)

all: $(NAME)

.SILENT:

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) -o $(NAME) $(OBJS) $(INCLUDE) $(RL_FLAGS)
	echo $(GREEN)"Building $(NAME)"$(DEFAULT);

$(LIBFT):
	make -C $(LIBFT_PATH)

$(BINDIR) $(PARSEDIR) $(BUILDDIR) $(EXECDIR) $(MAINDIR):
	mkdir -p $@

$(BINDIR)/%.o: %.c | $(BINDIR) $(PARSEDIR) $(BUILDDIR) $(EXECDIR) $(MAINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

submodule:
	git submodule update --init --recursive

clean:
	make clean -C $(LIBFT_PATH)
	rm -rf $(BINDIR)
	echo $(RED)"Removing $(NAME) object files"$(DEFAULT);

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_PATH)
	echo $(RED)"Removing $(NAME)"$(DEFAULT);

re: fclean all
	echo $(GREEN)"Rebuilding everything"$(DEFAULT);

.PHONY: all clean fclean re

# Colours
DEFAULT = "\033[39m"
GREEN = "\033[32m"
RED = "\033[31m"
