/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:03:52 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/14 12:03:52 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int	create_proc(t_etiquette *e)
{
	int	i;

	e->start_time = get_timestamp();
	i = -1;
	while (++i < e->nb_philo)
	{
		e->philos[i].pid = fork();
		if (e->philos[i].pid < 0)
			return (printf("Error while creating process\n"), 1);
		if (e->philos[i].pid == 0)
			strt_rtn(&e->philos[i], e);
		usleep(100);
	}
	laundry(e);
	return (0);
}

int	laundry(t_etiquette *e)
{
	int	i;
	int	sts;

	i = -1;
	while (++i < e->nb_philo)
	{
		waitpid(-1, &sts, 0);
		if (sts != 0)
		{
			i = -1;
			while (++i < e->nb_philo)
				kill(e->philos[i].pid, 15);
			break ;
		}
	}
	sem_close(e->forks);
	sem_close(e->logs);
	sem_close(e->meals);
	sem_unlink("/forks");
	sem_unlink("/logs");
	sem_unlink("/meals");
	return (0);
}

int	banquet(t_etiquette *e)
{
	if (create_proc(e))
		return (printf("Error while creating threads"), 1);
	return (0);
}
