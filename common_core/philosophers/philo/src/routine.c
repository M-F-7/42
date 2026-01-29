/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 12:21:46 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/12 16:55:46 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks_and_print(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	safe_handle_mutex(first, LOCK);
	safe_printf(philo, "has taken a fork");
	safe_handle_mutex(second, LOCK);
	safe_printf(philo, "has taken a fork");
}

static void	smart_usleep(long duration, t_info *info)
{
	long	start;
	int		end;

	start = get_time_ms();
	while (1)
	{
		pthread_mutex_lock(&info->end_mutex);
		end = info->end;
		pthread_mutex_unlock(&info->end_mutex);
		if (end || (get_time_ms() - start >= duration))
			break ;
		usleep(500);
	}
}

static char	*one_philo(t_philo *philo)
{
	safe_handle_mutex(philo->left_fork, LOCK);
	safe_printf(philo, "has taken a fork");
	usleep(philo->info->ttd);
	safe_handle_mutex(philo->left_fork, UNLOCK);
	return (NULL);
}

static void	routine(t_philo *philo, pthread_mutex_t *first,
		pthread_mutex_t *second)
{
	int	end;

	while (1)
	{
		pthread_mutex_lock(&philo->info->end_mutex);
		end = philo->info->end;
		pthread_mutex_unlock(&philo->info->end_mutex);
		if (end)
			break ;
		take_forks_and_print(philo, first, second);
		pthread_mutex_lock(&philo->meal_mutex);
		philo->last_meal = get_time_ms();
		philo->nb_meals++;
		pthread_mutex_unlock(&philo->meal_mutex);
		safe_printf(philo, "is eating");
		smart_usleep(philo->info->tte, philo->info);
		safe_handle_mutex(first, UNLOCK);
		safe_handle_mutex(second, UNLOCK);
		safe_printf(philo, "is sleeping");
		smart_usleep(philo->info->tts, philo->info);
		safe_printf(philo, "is thinking");
		smart_usleep(ttk(philo), philo->info);
	}
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	philo = (t_philo *)arg;
	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	if (philo->info->nb_philo == 1)
		return (one_philo(philo));
	if (philo->id % 2 == 0)
		usleep(5000);
	routine(philo, first, second);
	return (NULL);
}
