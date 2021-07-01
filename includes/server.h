/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 23:20:55 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/30 18:11:20 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H
# include <unistd.h>
# include <signal.h>
# define BUFFER_SIZE 1024
typedef struct s_message{
	char	chunk[8];
	char	chunk_bit;
	int		cursor;
	char	buffer[BUFFER_SIZE];
	int		ended_pid[1024];
	int		ended_count;
}	t_message;

#endif