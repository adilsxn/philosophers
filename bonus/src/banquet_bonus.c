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
#include <semaphore.h>

static int	create_proc(t_etiquette *e)
{
	int		i;
	t_philo	*p;

	i = -1;
	p = e->philos;
	e->start_time = get_timestamp();
	while (++i < e->nb_philo)
	{
		p[i].pid = fork();
		if (p[i].pid < 0)
			exit(1);
		if (p[i].pid == 0)
			strt_rtn((void *)&(p[i]));
	}
	return (0);
}

int	laundry_proc(t_etiquette *e)
{
	int	i;
	int	sts;

	i = -1;
	if (!e)
		return (1);
	waitpid(-1, &sts, 0);
	if (WIFEXITED(sts))
	{
		while (++i < e->nb_philo)
			kill(e->philos[i].pid, 15);
	}
	sem_close(e->forks);
    sem_close(e->superv);
    sem_close(e->print);
	sem_unlink("/forks");
    sem_unlink("/superv");
    sem_unlink("/print");
	free(e->philos);
	exit(0);
}

int	banquet(t_etiquette *e)
{
	if (create_proc(e))
		return (printf("Error while creating processes\n"), 1);
	if (laundry_proc(e))
		return (printf("Error while cleaning processes\n"), 2);
	return (0);
}
