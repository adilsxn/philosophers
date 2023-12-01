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


int	laundry(t_etq *e)
{
	int	i;

	sem_unlink(e->sem_c);
	sem_unlink(e->sem_t);
	sem_unlink(e->sem_p);
	sem_unlink(e->sem_f);
	i = -1;
	while (++i < e->nb_philo)
	{
		kill(e->philos[i].pid, 15);
		waitpid(e->philo[i].pid, NULL, WNOHANG)
	}
	free(e->philos);
}

t_exit bad_exit(t_etq *e)
{
	laundry(e);
	printf("Something went error\n");
	return (INVALID);
}

t_exit good_exit(t_etq *e)
{
	laundry(e);
	return (VALID);
}

int	banquet(t_etq *e)
{
	if (create_proc(e))
		return (printf("Error while creating processes\n"), 1);
	if (laundry_proc(e))
		return (printf("Error while cleaning processes\n"), 2);
	return (0);
}
