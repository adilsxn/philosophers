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

#include "../inc/philo_bonus.h"

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


void	solo_dolo(t_etq *e, t_philo *p)
{
	usleep(e->time_to_die * 1000);
	log_status(p, e, DEAD);
	pthread_mutex_unlock(p->left_fork);
	e->all_alive = 0;
	return ;
}