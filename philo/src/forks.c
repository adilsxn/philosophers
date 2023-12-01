/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:09:52 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/11/30 12:09:52 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	take_fork(t_ph *philo)
{
	if (pthread_mutex_lock(philo->e->mu_f) || log_status(philo, FORK)
		|| pthread_mutex_lock(philo->e->mu_f) || log_status(philo, FORK))
		pthread_mutex_unlock(&philo->e->mu_e);
}

void	put_fork(t_ph *philo)
{
	if (pthread_mutex_unlock(philo->e->mu_f)
	|| pthread_mutex_unlock(philo->e->mu_f))
		pthread_mutex_unlock(&philo->e->mu_e);
}
