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

#include "../inc/philo.h"

static int	init_etiq(t_etiquette *e, char **av, int ac)
{
	e->nb_philo = ft_atoi(av[1]);
	e->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * e->nb_philo);
	e->philos = (t_philo *)malloc(sizeof(t_philo) * e->nb_philo);
	if (!e->forks || !e->philos)
		return (1);
	e->time_to_die = ft_atoi(av[2]);
	e->time_to_eat = ft_atoi(av[3]);
	e->time_to_sleep = ft_atoi(av[4]);
	e->must_eat = -1;
	e->total_meals = 0;
	//e->start_time = get_timestamp(e);
	if (ac == 6)
		e->must_eat = ft_atoi(av[5]);
	return (0);
}

static int	init_mtx(t_etiquette *e)
{
	int	i;

	if (!e)
		return (1);
	i = e->nb_philo;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&e->forks[i], NULL)
		|| pthread_mutex_init(&e->philos[i].eating, NULL))
			return (2);
	}
	if (pthread_mutex_init(&e->check, NULL) 
	|| pthread_mutex_init(&e->print, NULL))
		return (2);

	return (0);
}

static int	init_phil(t_etiquette *e)
{
	int	i;

	if (!e)
		return (1);
	i = e->nb_philo;
	while (--i >= 0)
	{
		e->philos[i].id = i;
		e->philos[i].full = 0;
		e->philos[i].nb_meals = 0;
		e->philos[i].thread = 0;
		e->philos[i].left_fork = e->forks + i;
		e->philos[i].right_fork = e->forks + ((i + 1) % e->nb_philo);
		if (i % 2)
		{
			e->philos[i].left_fork  = e->forks + ((i + 1) % e->nb_philo);
			e->philos[i].right_fork = e->forks + i;  
		}
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
	if (init_mtx(e))
		return (printf("Error: initiating the mutexes"), 4);
	return (0);
}
