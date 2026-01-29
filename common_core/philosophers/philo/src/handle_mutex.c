/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 13:38:04 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/12 16:27:09 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_mutex_error(int status, t_mutex code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		printf("Invalid mutex value\n");
	else if (status == EINVAL && code == INIT)
		printf("Invalid attr value\n");
	else if (status == EDEADLK)
		printf("A deadlock occur\n");
	else if (status == EPERM)
		printf("There is no lock\n");
	else if (status == EBUSY)
		printf("The mutex is already locked\n");
	else
		printf("Unknown mutex error");
}

void	safe_handle_mutex(pthread_mutex_t *mtx, t_mutex code)
{
	if (code == INIT)
		handle_mutex_error(pthread_mutex_init(mtx, NULL), code);
	else if (code == LOCK)
		handle_mutex_error(pthread_mutex_lock(mtx), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mtx), code);
	else if (code == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mtx), code);
}
