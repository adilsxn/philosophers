/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:47:24 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 17:23:25 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	timer(time_t *val)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	*val = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (0);
}

void	lapse(t_ph *philo, time_t start, time_t limit)
{
	time_t	tmp;

	if (!start)
		if (timer(&start))
			pthread_mutex_unlock(&philo->e->mu_e);
	while (1)
	{
		if (timer(&tmp))
			pthread_mutex_unlock(&philo->e->mu_e);
		if (tmp - start >= limit)
			break ;
		if (usleep(100) == -1)
			pthread_mutex_unlock(&philo->e->mu_e);
	}
}
