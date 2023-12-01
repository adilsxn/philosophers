/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:00:10 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 21:35:00 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*famine(void *arg)
{
	t_ph	*philo;
	time_t	tmp;

	philo = (t_ph *)arg;
	lapse(philo, 0, philo->e->time_to_die - 10);
	while (1)
	{
		if (timer(&tmp))
			pthread_mutex_unlock(&philo->e->mu_e);
		if (tmp - philo->time > philo->e->time_to_die)
		{
			log_status(philo, DEAD);
			pthread_mutex_unlock(&philo->e->mu_e);
		}
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_ph	*philo;

	philo = (t_ph *)arg;
	if (philo->id % 2)
		lapse(philo, 0, 100 * 10);
	if (timer(&philo->time))
		pthread_mutex_unlock(&philo->e->mu_e);
	while (1)
	{
		take_fork(philo);
		ph_eat(philo);
		put_fork(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}
