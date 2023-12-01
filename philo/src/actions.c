/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:25:49 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 21:33:40 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	ph_eat(t_ph *philo)
{
	if (log_status(philo, EAT) || timer(&philo->time))
		pthread_mutex_unlock(&philo->e->mu_e);
	(philo->meals)++;
	lapse(philo, philo->time, philo->e->time_to_eat);
	if (philo->e->must_eat && philo->meals == philo->e->must_eat)
		if (++(philo->enough) == philo->e->nb_philo)
			if (log_status(philo, FULL))
				pthread_mutex_unlock(&philo->e->mu_e);
}

void	ph_sleep(t_ph *philo)
{
	if (log_status(philo, SLEEP))
		pthread_mutex_unlock(&philo->e->mu_e);
	lapse(philo, 0, philo->e->time_to_sleep);
}

void	ph_think(t_ph *philo)
{
	if (log_status(philo, THINK))
		pthread_mutex_unlock(&philo->e->mu_e);
}
