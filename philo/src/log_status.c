/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:54:15 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/04 15:10:22 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static char	*get_status(t_ph_status status)
{
	if (status == THINK)
		return ("\033[0;36m is thinking\033[0;0m");
	if (status == EAT)
		return ("\033[0;32m is eating\033[0;0m");
	if (status == DEAD)
		return ("\033[0;31m died\033[0;0m");
	if (status == SLEEP)
		return ("\033[0;35m is sleeping\033[0;0m");
	if  (status == FORK)
		return ("\033[1;33m has taken a fork\033[0;0m");
	return ("ERROR");
}

void	log_status(t_philo *p, t_etiquette *e, t_ph_status status)
{
	long long tmp;
	
	pthread_mutex_lock(&e->print);
	if (is_flag_on(e) == 1)
	{
	 	pthread_mutex_unlock(&e->print);
	 	return ;
	}
	tmp = get_timestamp() - e->start_time;
	printf("[%lld]\t%i\t%s\n", tmp, (p->id + 1), get_status(status));
	pthread_mutex_unlock(&e->print);
}
