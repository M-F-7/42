/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:42:28 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/12 17:05:42 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	safe_printf(t_philo *philo, const char *msg)
{
	long	timestamp;

	timestamp = get_time_ms() - philo->info->start_time;
	pthread_mutex_lock(&philo->info->print_mutex);
	pthread_mutex_lock(&philo->info->end_mutex);
	if (!philo->info->end)
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->info->end_mutex);
	pthread_mutex_unlock(&philo->info->print_mutex);
}

long	get_time_ms(void)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}
