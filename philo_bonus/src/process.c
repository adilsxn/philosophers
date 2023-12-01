/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:18:37 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 14:47:07 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*gluttony(void *arg)
{
	t_etq	*e;
	int		counter;

	e = (t_etq *)arg;
	counter = 0;
	while (1)
	{
		if (sem_wait(e->sem_c) == -1)
			sem_post(e->sem_e);
		if (++counter && counter == e->must_eat)
		{
			log_status(e, FULL);
			sem_post(e->sem_e);
		}
	}
	return (NULL);
}

void	*famine(void *arg)
{
	t_etq	*e;
	time_t	tmp;

	e = (t_etq *)arg;
	lapse(e, 0, e->time_to_die - 10);
	while (1)
	{
		if (timer(&tmp))
			sem_post(e->sem_e);
		if (tmp - e->philos[e->id].time > e->time_to_die)
		{
			log_status(e, DEAD);
			sem_post(e->sem_e);
		}
	}
	return (NULL);
}

void	routine(t_etq *e)
{
	if (pthread_create(&e->philos[e->id].th, NULL, famine, (void *)e)
		|| pthread_detach(e->philos[e->id].th))
		sem_post(e->sem_e);
	if (e->id % 2)
		lapse(e, 0, 100 * 10);
	if (timer(&e->philos[e->id].time))
		sem_post(e->sem_e);
	while (1)
	{
		take_fork(e);
		ph_eat(e);
		put_fork(e);
		ph_sleep(e);
		ph_think(e);
	}
}
