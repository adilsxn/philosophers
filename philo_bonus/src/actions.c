/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:25:49 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 14:51:18 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	ph_eat(t_etq *e)
{
	if (log_status(e, EAT) || timer(&e->philos[e->id].time))
		sem_post(e->sem_e);
	(e->philos[e->id].meals)++;
	lapse(e, e->philos[e->id].time, e->time_to_eat);
	if (e->must_eat && e->philos[e->id].meals == e->must_eat)
		if (sem_post(e->sem_c) == -1)
			sem_post(e->sem_e);
}

void	ph_sleep(t_etq *e)
{
	if (log_status(e, SLEEP))
		sem_post(e->sem_e);
	lapse(e, 0, e->time_to_sleep);
}

void	ph_think(t_etq *e)
{
	if (log_status(e, THINK))
		sem_post(e->sem_e);
}
