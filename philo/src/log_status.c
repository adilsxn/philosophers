/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_status.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:54:15 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/05 14:55:23 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	get_status(t_status status)
{
	if (status == THINK)
		printf("\033[0;36m is thinking\033[0;0m\n");
	else if (status == EAT)
		printf("\033[0;32m is eating\033[0;0m\n");
	else if (status == DEAD)
		printf("\033[0;31m died\033[0;0m\n");
	else if (status == SLEEP)
		printf("\033[0;35m is sleeping\033[0;0m\n");
	else if  (status == FORK1 || status == FORK2)
		printf("\033[1;33m has taken a fork\033[0;0m\n");
}

void	log_status(t_philo *p, t_status status, int flag)
{
	long long tmp;
	
	pthread_mutex_lock(&p->rules->print);
	if (is_flag_on(p->rules) == 1 && flag == 0)
	{
	 	pthread_mutex_unlock(&p->rules->print);
	 	return ;
	}
	tmp = get_timestamp() - p->rules->start_time;
	printf("%lld\t%i\t", tmp, (p->id + 1));
	get_status(status);
	pthread_mutex_unlock(&p->rules->print);
}
