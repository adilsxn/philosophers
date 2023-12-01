/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:03:52 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 20:45:44 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"


/**
 * @brief Function to handle laundry for a philosopher.
 * 
 * This function is responsible for handling the laundry task for a philosopher.
 * It takes a pointer to a `t_ph` structure as a parameter.
 * 
 * @param philo A pointer to a `t_ph` structure representing the philosopher.
 */
static void laundry(t_ph *philo)
{
	int	i;

	i = -1;
	if ((philo->e->mu_f))
	{
		while (++i < philo->e->nb_philo)
			pthread_mutex_destroy(&philo->e->mu_f[i]);
		ffree(philo->e->mu_f);
		ffree(philo);
	}
	pthread_mutex_destroy(&philo->e->mu_e);
	pthread_mutex_destroy(&philo->e->mu_p);
}

t_exit	bad_exit(t_ph *philo)
{
	laundry(philo);
	printf("Something went wrong\n");
	printf(MSG);
	return (INVALID);
}

t_exit	good_exit(t_ph *philo)
{
	laundry(philo);
	return (VALID);
}
