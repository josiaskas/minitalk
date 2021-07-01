/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 23:23:27 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/30 22:28:23 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/server.h"

t_message	g_data;

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s)
		while (s[i] != '\0')
			write(fd, &s[i++], 1);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	nbr;

	nbr = (long)n;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nbr;
	}
	if (nbr > 9)
		ft_putnbr_fd((nbr / 10), fd);
	ft_putchar_fd(('0' + (nbr % 10)), fd);
}

void	ft_recieve_chunks(int i)
{
	if (i == 1)
		g_data.chunk[g_data.chunk_bit] = 1;
	else
		g_data.chunk[g_data.chunk_bit] = 0;
	g_data.chunk_bit++;
}

void	ft_merge_chunks(void)
{
	int		bit;
	int		multi;
	char	data;

	data = 0;
	bit = 0;
	while (bit < 8)
	{
		multi = 1;
		multi = multi << bit;
		data += g_data.chunk[bit] * multi;
		bit++;
	}
	g_data.buffer[g_data.cursor] = data;
	g_data.cursor++;
}

void	signal_handler(int signal)
{
	int	type;
	int	cursor;

	type = 0;
	cursor = g_data.cursor;
	if (signal == SIGUSR1)
		type = 1;
	if (g_data.chunk_bit < 7)
		ft_recieve_chunks(type);
	else
	{
		ft_recieve_chunks(type);
		g_data.chunk_bit = 0;
		ft_merge_chunks();
		if ((cursor >= BUFFER_SIZE - 1) || (g_data.buffer[cursor] == 0))
		{
			ft_putstr_fd("BUFFER : ", STDOUT_FILENO);
			g_data.buffer[cursor + 1] = 0;
			ft_putstr_fd(g_data.buffer, STDOUT_FILENO);
			g_data.cursor = 0;
			g_data.buffer[0] = 0;
		}
	}
}

int		main(void)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sa.sa_handler = signal_handler;
	g_data.chunk_bit = 0;
	g_data.cursor = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_putstr_fd("Server listening with PID:", STDOUT_FILENO);
	ft_putnbr_fd(getpid(), STDOUT_FILENO);
	ft_putchar_fd(10, STDOUT_FILENO);
	while (1)
	{
		pause();
	}
	return (0);
}
