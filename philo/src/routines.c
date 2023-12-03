/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:05:08 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/03 17:37:00 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*solo_dolo(t_etiquette *e, t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	log_status(p, e, FORK);
	_sleep(e, e->time_to_die);
	log_status(p, e, DEAD);
	pthread_mutex_unlock(p->left_fork);
	return (NULL);
}

void	*strt_rtn(void *arg)
{
	t_philo		*p;
	t_etiquette	*e;

	p = (t_philo *)arg;
	e = p->rules;
	pthread_mutex_lock(&p->eating);
	p->meal_time = e->start_time;
	pthread_mutex_unlock(&p->eating);
	if (p->id % 2)
		_sleep(e, 1500);
	if (e->nb_philo == 1)
		return(solo_dolo(e, p));
	while (is_running(e))
		life(p, e);
	return (NULL);
}


void	*checker(void *arg)
{
	int			i;
	t_philo		*p;
	t_etiquette	*e;

	e = (t_etiquette *)arg;
	p = e->philos;
	while (is_running(e))
	{
		i = -1;
		while (++i < e->nb_philo && is_running(e))
		{
			death(&p[i], e);
			usleep(100);
		}
		i = 0;
		while (e->must_eat != -1 && i < e->nb_philo &&
				p[i].nb_meals >= e->must_eat)
			i++;
		if (i == e->nb_philo)
			stopping(e);
	}
	return (NULL);
}
