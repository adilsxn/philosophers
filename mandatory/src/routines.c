/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:05:08 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/14 12:05:08 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
#include <unistd.h>

void	*strt_rtn(void *arg)
{
	t_philo		*p;
	t_etiquette	*e;

	p = (t_philo *)arg;
	e = p->rules;
	if (e->nb_philo == 1)
		return (solo_dolo(e, p));
	delayed_start(p);
	while (e->all_alive && e->total_meals != e->nb_philo)
		life(p, e);
	return (NULL);
}

int	dth_chck(t_etiquette *e)
{
	int	i;

	i = -1;
	while (++i < e->nb_philo)
	{
		if (death(e->philos[i], e))
			return (1);
		if (e->philos[i]->nb_meals == e->must_eat && !e->philos[i]->full)
		{
			e->total_meals++;
			e->philos[i]->full = 1;
		}
		if (e->total_meals == e->nb_philo)
			return (1);
	}
	return (0);
}

void	*checker(void *arg)
{
	t_etiquette	*e;

	e = (t_etiquette *)arg;
	while (e->all_alive)
	{
		if (dth_chck(e))
			break ;
		usleep(1200);
	}
	return (NULL);
}
