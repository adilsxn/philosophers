/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_table.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 11:34:22 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/14 11:34:22 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int	init_etiq(t_etiquette *e, char **av, int ac)
{
	e->nb_philo = ft_atoi(av[1]);
	e->philos = (t_philo *)malloc(sizeof(t_philo) * e->nb_philo);
	if (!e->philos)
		return (1);
	e->time_to_die = ft_atoi(av[2]);
	e->time_to_eat = ft_atoi(av[3]);
	e->time_to_sleep = ft_atoi(av[4]);
	e->must_eat = -1;
	e->all_fed = 0;
	e->all_alive = 1;
	e->start_time = get_timestamp();
	if (ac == 6)
		e->must_eat = ft_atoi(av[5]);
	return (0);
}

static int	init_sem(t_etiquette *e)
{
	if (!e)
		return (1);
	sem_unlink("/forks");
	e->forks = sem_open("/forks", O_CREAT, S_IRWXU, e->nb_philo);
	if (e->forks == SEM_FAILED)
		return (1);
	return (0);
}

static int	init_phil(t_etiquette *e)
{
	int		i;

	if (!e)
		return (1);
	i = e->nb_philo;
	while (--i >= 0)
	{
		e->philos[i].id = i;
		e->philos[i].full = 0;
		e->philos[i].nb_meals = 0;
		e->philos[i].meal_time = e->start_time;
		e->philos[i].rules = e;
	}
	return (0);
}

int	set_table(t_etiquette *e, char **av, int ac)
{
	if (init_etiq(e, av, ac))
		return (1);
	if (init_phil(e))
		return (printf("Error: initiating philosophers"), 3);
	if (init_sem(e))
		return (printf("Error: initiating the mutexes"), 4);
	return (0);
}
