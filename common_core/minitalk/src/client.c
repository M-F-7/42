/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:09:53 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/13 11:05:34 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_msg_received = 0;

static void	handler(int signum)
{
	(void)signum;
	g_msg_received = 1;
}

void	transfer_message(char c, int pid)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		g_msg_received = 0;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_msg_received)
			usleep(10);
		bit++;
	}
}

static void	check_args(int ac)
{
	if (ac != 3)
	{
		ft_putstr_fd("Expected:./client SERVER_PID 'message'\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	main(int ac, char **av)
{
	int		pid;
	char	*message;
	int		i;

	check_args(ac);
	pid = ft_atoi(av[1]);
	message = av[2];
	i = 0;
	if (pid <= 0 || pid > 2147483647)
	{
		ft_putstr_fd("PID must be positive and not null, > INT_MAX\n", 2);
		exit(EXIT_FAILURE);
	}
	if (kill(pid, 0) < 0)
	{
		ft_putstr_fd("Error when sending a message to this PID\n", 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, handler);
	while (message[i])
		transfer_message(message[i++], pid);
	transfer_message('\n', pid);
	transfer_message('\0', pid);
	exit(EXIT_SUCCESS);
}
