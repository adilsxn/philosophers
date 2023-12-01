/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:25:49 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 17:21:16 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ph_eat(t_ph *philo)
{
	if (log_status(philo->e, EAT) || timer(&philo->time))
		pthread_mutex_unlock(&philo->e->mu_e);
	(philo->meals)++;
	lapse(philo->e, philo->time, philo->e->time_to_eat);
	if (philo->e->must_eat && philo->meals == philo->e->must_eat)
		if (pthread_mutex_unlock(&philo->e->sem_c) == -1)
			pthread_mutex_unlock(&philo->e->mu_e);
}

void	ph_sleep(t_ph *philo)
{
	if (log_status(e, SLEEP))
		pthread_mutex_unlock(&philo->e->mu_e);
	lapse(philo->e, 0, philo->e->time_to_sleep);
}

void	ph_think(t_ph *philo)
{
	if (log_status(philo->e, THINK))
		pthread_mutex_unlock(&philo->e->mu_e);
}
