/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 23:20:55 by jkasongo          #+#    #+#             */
/*   Updated: 2021/07/01 01:07:39 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <unistd.h>
# include <signal.h>
# define BUFFER_SIZE 1024

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

typedef struct s_message{
	char	chunk;
	int		shift_bit;
	int		last_bit;
	int		cursor;
	char	buffer[BUFFER_SIZE];
	int		sender_pid;
	int		ended_message;
}	t_message;

#endif