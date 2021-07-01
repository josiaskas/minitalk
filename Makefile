# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/01 02:18:25 by jkasongo          #+#    #+#              #
#    Updated: 2021/07/01 02:35:22 by jkasongo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER_NAME = server
CLIENT_NAME = client
CC = gcc
CFLAGS = -Wall -Wextra -Werror

#source
SRCS_SERVER =	server.c utils.c
SRCS_CLIENT =	client.c utils.c

OBJS_SERVER= $(SRCS_SERVER:%.c=%.o)
OBJS_CLIENT= $(SRCS_CLIENT:%.c=%.o)

all: $(SERVER_NAME) $(CLIENT_NAME)

$(SERVER_NAME): $(OBJS_SERVER)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) -o $(SERVER_NAME)
	@echo "server builded"

$(CLIENT_NAME): $(OBJS_CLIENT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $(CLIENT_NAME)
	@echo "client builded"

clean:
	@rm -f $(OBJS_SERVER)
	@rm -f $(OBJS_CLIENT)

fclean: 	clean
	@rm -f $(SERVER_NAME)
	@rm -f $(CLIENT_NAME)

re: fclean all

.PHONY:		all clean fclean re