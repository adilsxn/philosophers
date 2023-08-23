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

void	life(t_philo *p, t_etiquette *e)
{
	pthread_mutex_lock(p->left_fork);
	log_status(p, e, FORK);
	pthread_mutex_lock(p->right_fork);
	log_status(p, e, FORK);
	p->meal_time = get_timestamp();
	log_status(p, e, EAT);
	p->nb_meals++;
	usleep(e->time_to_eat * 1000);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	log_status(p, e, SLEEP);
	usleep(e->time_to_sleep * 1000);
	log_status(p, e, THINK);
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
		usleep(1500);
}
