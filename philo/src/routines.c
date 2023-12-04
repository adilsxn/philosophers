/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:05:08 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/04 22:26:20 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	life(t_philo *p, t_etiquette *e)
{
	pthread_mutex_lock(p->left_fork);
	log_status(p, e, FORK, 0);
	pthread_mutex_lock(p->right_fork);
	log_status(p, e, FORK, 0);
	log_status(p, e, EAT, 0);
	pthread_mutex_lock(&p->eating);
	p->meal_time = get_timestamp();
	pthread_mutex_unlock(&p->eating);
	_sleep(e, e->time_to_eat);
	if (is_flag_on(e) == 0)
	{
		pthread_mutex_lock(&p->eating);
		p->nb_meals++;
		pthread_mutex_unlock(&p->eating);
	}
	log_status(p, e, SLEEP, 0);
	pthread_mutex_unlock(p->left_fork);
	pthread_mutex_unlock(p->right_fork);
	_sleep(e, e->time_to_sleep);
}

static void ph_think(t_philo *p, int flag)
{
	long long  time_to_think;

	pthread_mutex_lock(&p->eating);
	time_to_think = (p->rules->time_to_die - 
	(get_timestamp() - p->meal_time) 
	- p->rules->time_to_eat) / 2;
	pthread_mutex_unlock(&p->eating);
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && flag == 1)
		time_to_think = 1;
	if (time_to_think > 600)
		time_to_think = 200;
	if (flag == 0)
		log_status(p, p->rules, THINK, 0);
	_sleep(p->rules, time_to_think);
}
static void	*solo_dolo(t_etiquette *e, t_philo *p)
{
	pthread_mutex_lock(p->left_fork);
	log_status(p, e, FORK, 0);
	_sleep(e, e->time_to_die);
	log_status(p, e, DEAD, 0);
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
	equal_start(e->start_time);
	if (p->id % 2)
		ph_think(p, 1);
	if (e->nb_philo == 1)
		return(solo_dolo(e, p));
	while (is_flag_on(e) == 0)
	{
		life(p, e);
		ph_think(p, 0);
	}
	return (NULL);
}

