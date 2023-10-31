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

void	*strt_rtn(void *arg)
{
	t_philo		*p;
	t_etiquette	*e;

	p = (t_philo *)arg;
	e = p->rules;
	if (e->nb_philo == 1)
		solo_dolo(e, p);
	delayed_start(p);
	while (e->all_alive && !e->all_fed)
		life(p, e);
	return (NULL);
}

void	*checker(void *arg)
{
	int			i;
	t_philo		*p;
	t_etiquette	*e;

	e = (t_etiquette *)arg;
	p = e->philos;
	while (!e->all_fed)
	{
		i = -1;
		while (++i < e->nb_philo && e->all_alive)
		{
			death(&p[i], e);
		}
		if (!e->all_alive)
			break ;
		i = 0;
		while (e->must_eat != -1 && i < e->nb_philo
			&& p[i].nb_meals >= e->must_eat)
			i++;
		if (i == e->nb_philo)
			e->all_fed = 1;
	}
	return (NULL);
}
