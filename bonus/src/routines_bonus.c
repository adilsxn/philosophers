/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:05:08 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/14 12:05:08 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	*strt_rtn(void *arg)
{
	t_philo		*p;
	t_etiquette	*e;

	p = (t_philo *)arg;
	e = p->rules;
	delayed_start(p);
	pthread_create(&(p->checker), NULL, checker, arg);
	pthread_detach(p->checker);
	while (e->all_alive)
	{
		life(p, e);
		if (e->must_eat != -1 && p->nb_meals >= e->must_eat)
			break ;
		log_status(p, e, SLEEP);
		usleep(e->time_to_sleep * 1000);
		log_status(p, e, THINK);
	}
	return (NULL); 
}

void	*checker(void *arg)
{
	t_philo *p;
	t_etiquette	*e;

	p = (t_philo *)arg;
	e = p->rules;
	while(1)
	{
		death(p, e);
		if (!e->all_alive)
			break ;
		usleep(1000);
		while (e->must_eat != -1 && p->nb_meals >= e->must_eat)
			break ;
	}
	return (NULL);
}