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

#include "../inc/philo.h"
#include <pthread.h>

// void think(t_philo *p, t_etiquette *e)
// {
//
// }

void	life(t_philo *p, t_etiquette *e)
{
	pthread_mutex_lock(p->left_fork);
	log_status(p, e, FORK1);
	pthread_mutex_lock(p->right_fork);
	log_status(p, e, FORK2);
	log_status(p, e, EAT);
	_sleep(e, e->time_to_eat);
	pthread_mutex_lock(&e->g_lock);
	p->meal_time = get_timestamp();
	pthread_mutex_unlock(&e->g_lock);
	if (!e->all_fed && e->all_fed)
	{
		pthread_mutex_lock(&e->g_lock);
		p->nb_meals++;
		pthread_mutex_unlock(&e->g_lock);
	}
	log_status(p, e, SLEEP);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	_sleep(e, e->time_to_sleep);
	log_status(p, e, THINK);
}

void	_sleep(t_etiquette *e, time_t time_to_spend)
{
	while (get_timestamp() < (get_timestamp() + time_to_spend))
	{
		if (!e->all_alive)
			break ;
		usleep(100);
	}
}

int	death(t_philo *p, t_etiquette *e)
{
	if (get_timestamp() - p->meal_time > e->time_to_die)
	{
		log_status(p, e, DEAD);
		e->all_alive = 0;
		return (1);
	}
	return (0);
}

void	delayed_start(t_philo *p)
{
	if (p->id % 2)
		log_status(p, p->rules, THINK);
}
