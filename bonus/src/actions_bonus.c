/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:13:13 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/07 12:13:13 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"
#include <semaphore.h>

void	life(t_philo *p, t_etiquette *e)
{
	sem_wait(e->forks);
	log_status(p, e, FORK);
	if (e->nb_philo == 1)
		solo_dolo(e, p);
	sem_wait(e->forks);
	log_status(p, e, FORK);
    sem_wait(e->superv);
	p->meal_time = get_timestamp();
	log_status(p, e, EAT);
	p->nb_meals++;
    sem_post(e->superv);
	usleep(e->time_to_eat * 1000);
	sem_post(e->forks);
	sem_post(e->forks);
}

int	death(t_philo *p, t_etiquette *e)
{
	if (get_timestamp() - p->meal_time > e->time_to_die)
	{
		log_status(p, e, DEAD);
		e->all_alive = 0;
		exit(1);
	}
	return (0);
}

void	delayed_start(t_philo *p)
{
	if (p->id % 2)
		usleep(1000);
}
