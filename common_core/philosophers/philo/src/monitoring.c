/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 14:49:07 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/12 17:28:48 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	put_end(t_info *info)
{
	pthread_mutex_lock(&info->end_mutex);
	info->end = TRUE;
	pthread_mutex_unlock(&info->end_mutex);
}

static int	check_philos(t_info *info, int *philo_full)
{
	int		i;
	long	time_hungry;

	i = -1;
	*philo_full = 0;
	while (++i < info->nb_philo)
	{
		pthread_mutex_lock(&info->philo[i].meal_mutex);
		time_hungry = get_time_ms() - info->philo[i].last_meal;
		if (time_hungry > info->ttd)
		{
			put_end(info);
			pthread_mutex_lock(&info->print_mutex);
			printf("%li %i died\n", get_time_ms() - info->start_time,
				info->philo[i].id);
			pthread_mutex_unlock(&info->print_mutex);
			pthread_mutex_unlock(&info->philo[i].meal_mutex);
			return (1);
		}
		if (info->max_meals > 0 && info->philo[i].nb_meals >= info->max_meals)
			(*philo_full)++;
		pthread_mutex_unlock(&info->philo[i].meal_mutex);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_info	*info;
	int		philo_full;

	info = (t_info *)arg;
	while (1)
	{
		pthread_mutex_lock(&info->end_mutex);
		if (info->end)
		{
			pthread_mutex_unlock(&info->end_mutex);
			break ;
		}
		pthread_mutex_unlock(&info->end_mutex);
		if (check_philos(info, &philo_full))
			return (NULL);
		if (info->max_meals > 0 && philo_full == info->nb_philo)
		{
			pthread_mutex_lock(&info->end_mutex);
			info->end = TRUE;
			pthread_mutex_unlock(&info->end_mutex);
			return (NULL);
		}
		usleep(50);
	}
	return (NULL);
}
