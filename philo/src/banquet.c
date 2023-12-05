/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banquet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:03:52 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/05 10:29:07 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	create_threads(t_etiquette *e)
{
	int	i;

	i = -1;
	e->start_time = get_timestamp() + (e->nb_philo * 2 * 10);
	while (++i < e->nb_philo)
	{
		if (pthread_create(&e->philos[i].thread, NULL, &strt_rtn, &e->philos[i]))
			return (1);
	}
	if (e->nb_philo > 1)
	{
		if (pthread_create(&e->checker, NULL, &checker, e))
			return (1);
	}
	return (0);
}

static int	join_threads(t_etiquette *e)
{
	int	i;

	i = -1;
	while (++i < e->nb_philo)
		pthread_join(e->philos[i].thread, NULL);
	if (e->nb_philo > 1)
		pthread_join(e->checker, NULL);
	return (0);
}

int	laundry(t_etiquette *e)
{
	int	i;

	i = -1;
	if (!e)
		return (1);
	while (++i < e->nb_philo)
	{
		pthread_mutex_destroy(&e->forks[i]);
		pthread_mutex_destroy(&e->philos[i].eating);
	}
	pthread_mutex_destroy(&e->check);
	pthread_mutex_destroy(&e->print);
	free(e->philos);
	free(e->forks);
	return (0);
}

int	banquet(t_etiquette *e)
{
	if (create_threads(e))
		return (printf("Error while creating threads"), 1);
	if (join_threads(e))
		return (printf("Error while joining threads"), 2);
	return (0);
}
