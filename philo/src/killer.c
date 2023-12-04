/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   killer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:57:45 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/04 17:00:21 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	death(t_philo *p, t_etiquette *e)
{
    long long cur;

    cur = get_timestamp();
    pthread_mutex_lock(&p->eating);
	if (cur - p->meal_time > e->time_to_die)
	{
        log_status(p, e, DEAD);
		set_stop_flag(e, 1);
        pthread_mutex_unlock(&p->eating);
		return (1);
	}
    pthread_mutex_unlock(&p->eating);
    usleep(100);
	return (0);
}

void	*checker(void *arg)
{
	int			i;
	t_philo		*p;
	t_etiquette	*e;
    int ate;

	e = (t_etiquette *)arg;
	p = e->philos;
    ate = 0;
	set_stop_flag(e, 0);
	while (is_flag_on(e) == 0)
	{
		i = -1;
		while (++i < e->nb_philo && is_flag_on(e) == 0)
		{
			death(&p[i], e);
            pthread_mutex_lock(&p[i].eating);
            if(e->must_eat != -1)
                if (p[i].nb_meals >= e->must_eat)
                     ate = 1;
            pthread_mutex_unlock(&p[i].eating);
            if ((e->must_eat != -1) && ate == 1)
			    set_stop_flag(e, 1);
        }
	}
	return (NULL);
}
