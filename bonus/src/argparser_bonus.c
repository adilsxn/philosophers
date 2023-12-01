/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:57:08 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/06 20:57:08 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	argparser(int argc, char *av[], t_etq *e)
{
	e->sem_c = "sem_count";
	e->sem_t = "sem_term";
	e->sem_p = "sem_print";
	e->sem_f = "sem_fork";
	if (argc < 5 || argc > 6)
		return (printf(MSG), 1);
	while (--argc > 0)
	if (!ft_atoi(av[1], &e->nb_philo) || e->nb_philo < 1 || e->nb_philo > 201
		|| !ft_atoi(av[2], &e->time_to_die) || e->time_to_die < 0
		|| !ft_atoi(av[3], &e->time_to_eat) || e->time_to_eat < 0
		|| !ft_atoi(av[4], &e->time_to_sleep) || e->time_to_sleep < 0)
		return (printf("Invalid parameters!\n"), 3);
	if (av[5] && !ft_atoi(av[5], &e->must_eat) || e->must_eat < 1)
		return (printf("Nbr times they must eat needs to be > 0!\n"), 4);
	e->philos = (t_philo *)malloc(sizeof(t_philo) * e->nb_philo);
	if (!e->philos)
		return (printf("Malloc error!\n"), 2);
	if ( init_sem(&e->superv, e->sem_c, 1)
		|| init_sem(&e->term, e->sem_t, 1)
		|| init_sem(&e->print, e->sem_p, 1)
		|| init_sem(&e->fork, e->sem_f, e->nb_philo))
		return (printf("Semaphore error!\n"), 2);
	return (0);
}
