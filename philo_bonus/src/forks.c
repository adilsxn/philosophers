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

#include "../inc/philo_bonus.h"

void	take_fork(t_etq *e)
{
	if (sem_wait(e->sem_f) == -1 || log_status(e, FORK)
		|| sem_wait(e->sem_f) == -1 || log_status(e, FORK))
		sem_post(e->sem_e);
}

void	put_fork(t_etq *e)
{
	if (sem_post(e->sem_f) == -1 || sem_post(e->sem_f) == -1)
		sem_post(e->sem_e);
}
