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

void	life(t_philo *p, t_etq *e)
{
	pthread_mutex_lock(p->left_fork);
	log_status(p, e, FORK1);
	if (e->nb_philo == 1)
		solo_dolo(e, p);
	pthread_mutex_lock(p->right_fork);
	log_status(p, e, FORK2);
	p->meal_time = get_timestamp();
	log_status(p, e, EAT);
	p->nb_meals++;
	_sleep(e, e->time_to_eat);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	log_status(p, e, SLEEP);
	_sleep(e, e->time_to_sleep);
	log_status(p, e, THINK);
}



int	death(t_philo *p, t_etq *e)
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
		usleep(1500);
}
