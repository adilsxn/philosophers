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

void	take_fork(t_etq *e)
{
	if (pthread_mutex_lock(e->sem_f) == -1 || log_status(e, FORK)
		|| pthread_mutex_lock(e->sem_f) == -1 || log_status(e, FORK))
		pthread_mutex_unlock(e->mu_e);
}

void	put_fork(t_etq *e)
{
	if (pthread_mutex_unlock(e->sem_f) == -1 || pthread_mutex_unlock(e->sem_f) == -1)
		pthread_mutex_unlock(e->mu_e);
}
