/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:09:43 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/06 22:09:43 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


int	ft_atoi(const char *str)
{
	int	sinal;
	int	res;

	res = 0;
	sinal = 1;
	while (*str == ' ' || (9 <= *str && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sinal = -sinal;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return ((int)(res * sinal));
}

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

static char	*get_status(t_ph_status status)
{
	if (status == THINK)
		return ("is thinking");
	if (status == EAT)
		return ("is eating");
	if (status == DEAD)
		return ("died");
	if (status == SLEEP)
		return ("is sleeping");
	if  (status == FORK)
		return ("has taken a fork");
	return ("ERROR");
}

void	log_status(t_philo *p, t_etiquette *e, t_ph_status status)
{
	long long tmp;
	
	 pthread_mutex_lock(&e->print);
	if (!is_running(e))
	{
	 	pthread_mutex_unlock(&e->print);
	 	return ;
	}
	tmp = get_timestamp() - e->start_time;
	{
		printf("[%lld]ms %i %s\n", tmp, (p->id + 1), get_status(status));
	}
	//pthread_mutex_unlock(&e->print);
}
