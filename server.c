/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 23:23:27 by jkasongo          #+#    #+#             */
/*   Updated: 2021/08/04 19:39:45 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/server.h"

t_message	g_data;

void	make_byte(int bit)
{
	g_data.last_bit = 0;
	if (g_data.shift_bit < 7)
	{	
		g_data.chunk += (bit << g_data.shift_bit);
		g_data.shift_bit++;
	}
	else
	{
		g_data.chunk += (bit << 7);
		g_data.shift_bit = 0;
		g_data.last_bit = 1;
	}
}

void	ft_merge_chunks(int pid)
{
	char	data;

	data = g_data.chunk;
	g_data.chunk = 0;
	g_data.shift_bit = 0;
	g_data.buffer[g_data.cursor] = data;
	g_data.sender_pid = pid;
	g_data.cursor++;
}

void	signal_handler(int signal, siginfo_t *info, void *ctx)
{
	int		type;
	int		cursor;

	(void)ctx;
	type = 0;
	cursor = g_data.cursor;
	g_data.ended_message = 0;
	if (signal == SIGUSR1)
		type = 1;
	make_byte(type);
	if (g_data.last_bit)
	{
		ft_merge_chunks(info->si_pid);
		if ((cursor >= (BUFFER_SIZE - 1)) || (g_data.buffer[cursor] == 0))
		{
			write(STDOUT_FILENO, &g_data.buffer, g_data.cursor);
			if (g_data.buffer[cursor] == 0)
			{
				write(STDOUT_FILENO, "\n", 1);
				g_data.ended_message = 1;
			}
			g_data.cursor = 0;
			g_data.buffer[0] = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sa.sa_mask = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putstr_fd("Server listening on PID:", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd(10, STDOUT_FILENO);
	while (1)
	{
		pause();
	}
	return (0);
}
