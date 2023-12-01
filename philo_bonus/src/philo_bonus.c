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

#include "../inc/philo_bonus.h"

/**
 * Parses the command line arguments and initializes the t_etq structure.
 * 
 * @param argc The number of command line arguments.
 * @param av The array of command line arguments.
 * @param e A pointer to the t_etq structure to be initialized.
 * @return Returns 0 if successful, otherwise returns an error code.
 */
int	argparser(int argc, char *av[], t_etq *e)
{
	e->c_name = "/sem_count";
	e->e_name = "/sem_exit";
	e->p_name = "/sem_print";
	e->f_name = "/sem_fork";
	if (argc < 5 || argc > 6)
		return (printf(MSG), 1);
	if (fatoi(av[1], &e->nb_philo) || e->nb_philo < 1 || e->nb_philo > 201
		|| fatoi(av[2], &e->time_to_die) || e->time_to_die < 0 || fatoi(av[3],
			&e->time_to_eat) || e->time_to_eat < 0 || fatoi(av[4],
			&e->time_to_sleep) || e->time_to_sleep < 0)
		return (printf("Invalid parameters!\n"), 3);
	if ((av[5] && fatoi(av[5], &e->must_eat)) || e->must_eat < 1)
		return (printf("Nbr times they must eat needs to be > 0!\n"), 4);
	if (fcalloc((void **)&e->philos, e->nb_philo, sizeof(t_ph)))
		return (printf("Malloc error!\n"), 2);
	if (init_sem(&e->sem_p, e->p_name, 1) || init_sem(&e->sem_e, e->e_name, 1)
		|| init_sem(&e->sem_c, e->c_name, 1) || init_sem(&e->sem_f, e->f_name,
			e->nb_philo))
		return (printf("Semaphore error!\n"), 2);
	return (0);
}

static int	ready_eat(t_etq *e)
{
	int	i;

	i = -1;
	if (pthread_create(&e->th, NULL, gluttony, (void *)e)
		|| pthread_detach(e->th) || timer(&(e->start)))
		return (1);
	while (++i < e->nb_philo)
	{
		e->id = i;
		e->philos[i].pid = fork();
		if (e->philos[i].pid == -1)
			return (1);
		else if (e->philos[i].pid == 0)
		{
			routine(e);
			exit(VALID);
		}
	}
	if (sem_wait(e->sem_e) == -1)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_etq	e;

	fmemset(&e, 0, sizeof(t_etq));
	if (argparser(argc, argv, &e))
		return (bad_exit(&e));
	if (ready_eat(&e))
		return (bad_exit(&e));
	return (good_exit(&e));
}