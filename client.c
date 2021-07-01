/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 01:31:36 by jkasongo          #+#    #+#             */
/*   Updated: 2021/06/30 00:48:52 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/client.h"

static int	ft_isspace_local(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int	ft_atoi(const char *str)
{
	long	nbr;
	int		sign;
	int		i;

	i = 0;
	nbr = 0;
	sign = 1;
	if (!str)
		return (0);
	while (str[i] != 0 && ft_isspace_local(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] != 0 && ft_isdigit(str[i]))
		nbr = (nbr * 10) + (str[i++] - '0');
	if (sign == -1)
		return ((int)(nbr * -1));
	return ((int)nbr);
}

void	send_byte(int pid, char byte)
{
	int	i;
	int	bit;

	bit = 0;
	i = 0;
	while (i < 8)
	{
		if (byte & (1 << i))
			bit = 1;
		else
			bit = 0;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(10);
	}
}

int	main(int argc, char	*argv[])
{
	int	pid;
	int	i;

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
	return (0);
}
