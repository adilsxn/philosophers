/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:00:10 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 17:12:02 by acuva-nu         ###   ########.fr       */
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
			pthread_mutex_unlock(&philo->e->mu_e));
		if (tmp - philo->time > philo->e->time_to_die)
		{
			log_status(philo->e, DEAD);
			pthread_mutex_unlock(&philo->e->mu_e);
		}
	}
	return (NULL);
}

void	routine(t_etq *e)
{
	if (pthread_create(&e->philos[e->id].th, NULL, famine, (void *)e)
		|| pthread_detach(e->philos[e->id].th))
		pthread_mutex_unlock(e->mu_e);
	if (e->id % 2)
		lapse(e, 0, 100 * 10);
	if (timer(&e->philos[e->id].time))
		pthread_mutex_unlock(e->mu_e);
	while (1)
	{
		take_fork(e);
		ph_eat(e);
		put_fork(e);
		ph_sleep(e);
		ph_think(e);
	}
}
