/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfernand <mfernand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 15:15:41 by mfernand          #+#    #+#             */
/*   Updated: 2025/06/12 16:27:11 by mfernand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	handle_thread_error(int status, t_thread code)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		printf("Insufficient resources to create another thread\n");
	else if (status == EPERM)
		printf("No permission\n");
	else if (status == EINVAL && code == CREATE)
		printf("Invalid settings in attr\n");
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		printf("This thread is not a joinable thread\n");
	else if (status == ESRCH)
		printf("No thread with the ID thread could be found\n");
	else
		printf("Unknown thread error: %d\n", status);
}

void	safe_handle_thread(pthread_t *thread, void *(*foo)(void *), void *data,
		t_thread code)
{
	if (code == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), code);
	else if (code == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		handle_thread_error(pthread_detach(*thread), code);
	else
		printf("Unknown thread code\n");
}
