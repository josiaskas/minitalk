/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 01:31:36 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/04 20:00:29 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/client.h"
#include <stdio.h>

void	send_byte(int pid, char byte)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (byte & (1 << i))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(25);
	}
}

void	signal_recieved_data(int signal)
{
	if (signal == SIGUSR1)
		write(STDOUT_FILENO, "\nServer : message received\n", 28);
}

int	main(int argc, char	*argv[])
{
	struct sigaction	sa;
	int					pid;
	int					i;

	sa.sa_flags = 0;
	sa.sa_handler = signal_recieved_data;
	sa.sa_mask = 0;
	sigaction(SIGUSR1, &sa, NULL);
	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != 0)
		{
			send_byte(pid, argv[2][i]);
			i++;
		}
		send_byte(pid, 0);
	}
	else
		write(STDOUT_FILENO, "usage : ./client PID message", 29);
	return (0);
}
