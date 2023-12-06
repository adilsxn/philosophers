/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:57:45 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/05 15:20:45 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	death(t_philo *p)
{
    long long cur;

    cur = get_timestamp();
	if ((cur - p->meal_time) >= p->rules->time_to_die)
	{
		set_stop_flag(p->rules, 1);
        log_status(p, DEAD, 1);
        pthread_mutex_unlock(&p->eating);
		return (1);
	}
	return (0);
}

static int is_final(t_etiquette *e)
{
	 int ate;
	 int i;

	 ate = 1;
	 i = -1;
	 while (++i < e->nb_philo)
	 {
		pthread_mutex_lock(&e->philos[i].eating);
		if (death(&e->philos[i]) == 1)
			return (1);
        if(e->must_eat != -1)
		{
        	if (e->philos[i].nb_meals
				< (unsigned int)e->must_eat)
                ate = 0;
		}
		pthread_mutex_unlock(&e->philos[i].eating);
	 }
	if ((e->must_eat != -1) && ate == 1)
	{
		set_stop_flag(e, 1);
		return (1);
	}
	return (0);
}

void	*checker(void *arg)
{
	t_etiquette	*e;

	e = (t_etiquette *)arg;
	set_stop_flag(e, 0);
	equal_start(e->start_time);
	while (1)
	{
		if (is_final(e) == 1)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
