/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:34:02 by vgoncalv          #+#    #+#             */
/*   Updated: 2023/08/06 20:29:18 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Parses the command line arguments and initializes the t_etq structure.
 * 
 * @param argc The number of command line arguments.
 * @param av The array of command line arguments.
 * @param e A pointer to the t_etq structure to be initialized.
 * @return Returns 0 if successful, otherwise returns an error code.
 */
int	argparser(int argc, char *av[], t_ph *philo, t_etq *e)
{
	int i;

	i = -1;
	if (argc < 5 || argc > 6)
		return (printf(MSG), 1);
	if (fatoi(av[1], &e->nb_philo) || e->nb_philo < 1 || e->nb_philo > 201
		|| fatoi(av[2], &e->time_to_die) || e->time_to_die < 0 || fatoi(av[3],
			&e->time_to_eat) || e->time_to_eat < 0 || fatoi(av[4],
			&e->time_to_sleep) || e->time_to_sleep < 0)
		return (printf("Invalid parameters!\n"), 3);
	if ((av[5] && fatoi(av[5], &e->must_eat)) || e->must_eat < 1)
		return (printf("Nbr times they must eat needs to be > 0!\n"), 4);
	if (fcalloc((void **)&philo, e->nb_philo, sizeof(t_ph))
		|| fcalloc((void **)&e->mu_f, e->nb_philo, sizeof(t_mu)))
		return (printf("Malloc error!\n"), 2);
	while(++i < e->nb_philo)
	{
		if (pthread_mutex_init(&e->mu_f[i], NULL)
		|| pthread_mutex_init(&e->mu_p, NULL)
		|| pthread_mutex_init(&e->mu_e, NULL))
			return (printf("Mutex init error!\n"), 2);
	}
	return (0);
}

static int	ready_eat(t_etq *e, t_ph *philo)
{
	int	i;

	i = -1;
	if (pthread_mutex_lock(&e->mu_e) || timer(&e->start))
		return (1);
	while (++i < e->nb_philo)
	{
		philo[i].id = i;
		philo[i].e = e;
		philo[i].right = (i + 1) % e->nb_philo;
		philo[i].left = i;
		if (pthread_create(&philo[i].th, NULL, routine, (void *)(&philo[i]))
		|| pthread_detach(philo[i].th))
			return (1);
		if (pthread_create(&philo[i].th, NULL, famine, (void *)(&philo[i]))
		|| pthread_detach(philo[i].th))
			return (1);
	}
	if (pthread_mutex_lock(&e->mu_e))
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_etq	e;
	t_ph	*philo;

	fmemset(&e, 0, sizeof(t_etq));
	philo = NULL;
	if (argparser(argc, argv, philo, &e))
		return (bad_exit(philo));
	if (ready_eat(&e, philo))
		return (bad_exit(philo));
	return (good_exit(philo));
}
