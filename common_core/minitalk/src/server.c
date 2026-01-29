/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 19:09:50 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/13 10:59:27 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	handler(int signum)
{
	(void)signum;
	ft_putstr_fd("\nThe server has been stopped\n", 1);
	ft_putstr_fd("The message has been clearly transfered \n", 1);
	exit(EXIT_SUCCESS);
}

void	handle_signal(int signum, siginfo_t *data, void *empty)
{
	static int	nb_bit = 0;
	static char	curr_char = 0;
	int			pid;

	(void)empty;
	pid = data->si_pid;
	if (signum == SIGUSR1)
		curr_char |= (1 << nb_bit);
	nb_bit++;
	if (nb_bit == 8)
	{
		ft_printf("%c", curr_char);
		if (curr_char == '\0')
		{
			kill(pid, SIGUSR1);
		}
		curr_char = 0;
		nb_bit = 0;
	}
	kill(pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	s_action;

	ft_printf("%d\n", getpid());
	s_action.sa_flags = SA_SIGINFO;
	s_action.sa_sigaction = handle_signal;
	sigemptyset(&s_action.sa_mask);
	sigaction(SIGUSR1, &s_action, NULL);
	sigaction(SIGUSR2, &s_action, NULL);
	signal(SIGINT, handler);
	while (1)
		pause();
}
