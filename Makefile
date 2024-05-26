# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkremer <dkremer@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/16 20:17:05 by dhasan            #+#    #+#              #
#    Updated: 2024/05/26 18:18:48 by dkremer          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RL_FLAGS = -lreadline

# LIBFT_PATH = ./libft
# LIBFT = $(LIBFT_PATH)/libft.a

# INCLUDE =  -L $(LIBFT_PATH) -lft

SRCS = cd.c echo.c main.c pwd.c signal.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@cc $(CFLAGS)  -o $(NAME) $(OBJS) $(INCLUDE) $(RL_FLAGS)
# $(LIBFT) $(LIBFT)
# $(LIBFT):
# 	@make -C $(LIBFT_PATH)

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
# @make clean -C $(LIBFT_PATH)
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
# @make fclean -C $(LIBFT_PATH)

re: fclean all

.PHONY: all clean fclean re