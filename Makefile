# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhasan <dhasan@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/31 15:40:08 by dhasan            #+#    #+#              #
#    Updated: 2024/07/18 22:40:13 by dkremer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -I/inc
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
SRCS = \
	parsing/built_tree.c \
	parsing/built_tree_utils.c \
	parsing/built_tree_arrays.c \
	parsing/expander_utils.c \
	parsing/token_processing.c \
	parsing/node_utils.c \
	parsing/parse.c \
	parsing/token_utils.c \
	parsing/token_utils_2.c \
	parsing/token.c \
	builtins/cd.c \
	builtins/echo_env_pwd.c \
	builtins/export.c \
	builtins/export_utils.c \
	builtins/unset.c \
	builtins/exit.c \
	exec/builtin.c \
	exec/cmd_path.c \
	exec/command.c \
	exec/execution.c \
	exec/redirect.c \
	exec/pipe.c \
	exec/pipe_utils.c \
	main/env_utils.c \
	main/free.c \
	main/signal.c \
	main/main.c \
	main/utils.c \
	main/error_msg.c \
	main/error_msg_2.c \
	main/input.c

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
