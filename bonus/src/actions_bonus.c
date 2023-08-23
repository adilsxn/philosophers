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

void	life(t_philo *p, t_etiquette *e)
{
	sem_wait(e->forks);
	log_status(p, e, FORK);
	sem_wait(e->forks);
	log_status(p, e, FORK);
	p->meal_time = get_timestamp();
	sem_wait(e->meals);
	log_status(p, e, EAT);
	p->nb_meals++;
	sem_post(e->meals);
	usleep(e->time_to_eat * 1000);
	sem_post(e->forks);
	sem_post(e->forks);
}

void	*checker(void *arg)
{
	t_philo		*p;
	t_etiquette	*e;

	p = (t_philo *)arg;
	e = p->rules;
	while (1)
	{
		sem_wait(e->meals);
		if (get_timestamp() - p->meal_time > e->time_to_die)
		{
			log_status(p, e, DEAD);
			e->all_alive = 0;
			sem_wait(e->logs);
			exit(1);
		}
		sem_post(e->meals);
		if (!(e->all_alive))
			break ;
		usleep(1000);
		if (p->nb_meals >= e->nb_they_can_eat && e->nb_they_can_eat == -1)
			break ;
	}
	return (NULL);
}

int	strt_rtn(t_philo *p_arg, t_etiquette *e_arg)
{
	t_philo		*p;
	t_etiquette	*e;

	p = p_arg;
	e = e_arg;
	p->meal_time = get_timestamp();
	pthread_create(&p->checker, NULL, checker, p_arg);
	delayed_start(p);
	if (e->nb_philo == 1)
		return (solo_dolo(e, p));
	while (e->all_alive)
	{
		life(p, e);
		if (p->nb_meals >= e->nb_they_can_eat && e->nb_they_can_eat != -1)
			break ;
		log_status(p, e, SLEEP);
		usleep(e->time_to_sleep * 1000);
		log_status(p, e, THINK);
	}
	pthread_join(p->checker, NULL);
	if (!(e->all_alive))
		exit(1);
	exit(0);
}

void	delayed_start(t_philo *p)
{
	if (p->id % 2)
		usleep(15000);
}
