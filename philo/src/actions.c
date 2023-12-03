/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 12:13:13 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/03 17:26:34 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


void	life(t_philo *p, t_etiquette *e)
{
	pthread_mutex_lock(p->left_fork);
	log_status(p, e, FORK);
	pthread_mutex_lock(p->right_fork);
	log_status(p, e, FORK);
	log_status(p, e, EAT);
	pthread_mutex_lock(&p->eating);
	p->meal_time = get_timestamp();
	pthread_mutex_unlock(&p->eating);
	_sleep(e, e->time_to_eat);
	if (!is_running(e))
	{
		pthread_mutex_lock(&p->eating);
		p->nb_meals++;
		pthread_mutex_unlock(&p->eating);
	}
	log_status(p, e, SLEEP);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	_sleep(e, e->time_to_sleep);
	log_status(p, e, THINK);
}

void	_sleep(t_etiquette *e, time_t time_to_spend)
{
	long long tmp;

	tmp = get_timestamp() + time_to_spend;

	while (get_timestamp() < tmp)
	{
		if (!is_running(e))
			break ;
		usleep(100);
	}
}

int	death(t_philo *p, t_etiquette *e)
{
	if (get_timestamp() - p->meal_time > e->time_to_die - 10)
	{
		log_status(p, e, DEAD);
		stopping(e);
		return (1);
	}
	return (0);
}
