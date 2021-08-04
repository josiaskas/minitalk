# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 02:18:25 by jkasongo          #+#    #+#              #
#    Updated: 2021/08/04 19:41:12 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_NAME = server
CLIENT_NAME = client
CC = gcc
CFLAGS = -Wall -Wextra -Werror

#source
SRCS_SERVER =	server.c utils.c
SRCS_CLIENT =	client.c utils.c
#bonus source
SRCS_SERVER_BONUS =	server_bonus.c utils.c
SRCS_CLIENT_BONUS =	client_bonus.c utils.c

OBJS_SERVER= $(SRCS_SERVER:%.c=%.o)
OBJS_CLIENT= $(SRCS_CLIENT:%.c=%.o)
#bonus object
OBJS_SERVER_BONUS= $(SRCS_SERVER_BONUS:%.c=%.o)
OBJS_CLIENT_BONUS= $(SRCS_CLIENT_BONUS:%.c=%.o)

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(OBJS_SERVER)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER_NAME)
	@echo "server builded"
$(CLIENT_NAME): $(OBJS_CLIENT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT_NAME)
	@echo "client builded"
clean:
	@rm -f $(OBJS_SERVER)
	@rm -f $(OBJS_SERVER_BONUS)
	@rm -f $(OBJS_CLIENT)
	@rm -f $(OBJS_CLIENT_BONUS)
fclean: 	clean
	@rm -f $(SERVER_NAME)
	@rm -f $(CLIENT_NAME)
#building bonus
bonus: fclean $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	@$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) -o $(SERVER_NAME)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) -o $(CLIENT_NAME)
	@echo "bonus server and client builded"
re: fclean all

.PHONY:		all clean fclean re
