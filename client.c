/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 01:31:36 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/04 19:35:43 by jkasongo         ###   ########.fr       */
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

int	main(int argc, char	*argv[])
{
	int					pid;
	int					i;

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
