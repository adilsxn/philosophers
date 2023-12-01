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

int	argparser(int argc, char *av[], t_etq *e)
{
	e->c_name = "/sem_count";
	e->t_name = "/sem_term";
	e->p_name = "/sem_print";
	e->f_name = "/sem_fork";
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
	if ( init_sem(&e->sem_p, e->p_name, 1)
		|| init_sem(&e->sem_t, e->t_name, 1)
		|| init_sem(&e->sem_c, e->c_name, 1)
		|| init_sem(&e->sem_f, e->f_name, e->nb_philo))
		return (printf("Semaphore error!\n"), 2);
	return (0);
}

static int	create_proc(t_etq *e)
{
	int		i;

	i = -1;
if (pthread_create(&e->th, NULL, supervisor, (void *)e) 
	|| pthread_detach(e->th) || )
		return (1);
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

int	main(int argc, char *argv[])
{
	t_etq	e;

	memset(&e, 0, sizeof(t_etq)
	if (argparser(argc, argv))
		return (1);
	if (set_table(&e, argv, argc))
		return (2);
	banquet(&e);
	return (0);
}
