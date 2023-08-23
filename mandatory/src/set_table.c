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
	e->philos = (t_philo **)malloc(sizeof(t_philo *) * e->nb_philo);
	if (!e->forks || !e->philos)
		return (1);
	e->time_to_die = ft_atoi(av[2]);
	e->time_to_eat = ft_atoi(av[3]);
	e->time_to_sleep = ft_atoi(av[4]);
	e->nb_they_can_eat = -1;
	e->all_fed = 0;
	e->all_alive = 1;
	e->total_meals = 0;
	e->start_time = get_timestamp();
	if (ac == 6)
		e->nb_they_can_eat = ft_atoi(av[5]);
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
		if (pthread_mutex_init(&e->forks[i], NULL))
			return (2);
	}
	return (0);
}

static int	init_phil(t_etiquette *e)
{
	int		i;
	t_philo	*p;

	if (!e)
		return (1);
	i = e->nb_philo;
	while (--i >= 0)
	{
		p = (t_philo *)malloc(sizeof(t_philo));
		if (!p)
			return (2);
		p->id = i;
		p->full = 0;
		p->nb_meals = 0;
		p->thread = 0;
		p->left_fork = e->forks + i;
		p->right_fork = e->forks + ((i + 1) % e->nb_philo);
		p->meal_time = e->start_time;
		p->rules = e;
		e->philos[i] = p;
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
