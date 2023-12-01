/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 12:03:52 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 15:31:48 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

/**
 * @brief Performs the laundry operation.
 *
 * This function is responsible for performing the laundry operation
 * on the given t_etq structure.
 *
 * @param e The t_etq structure to perform the laundry operation on.
 * @return 0 on success.
 */
static int	laundry(t_etq *e)
{
	int	i;

	i = -1;
	sem_unlink(e->c_name);
	sem_unlink(e->e_name);
	sem_unlink(e->p_name);
	sem_unlink(e->f_name);
	while (++i < e->nb_philo)
	{
		kill(e->philos[i].pid, 15);
		waitpid(e->philos[i].pid, NULL, WNOHANG);
	}
	free(e->philos);
	return (0);
}

t_exit	bad_exit(t_etq *e)
{
	laundry(e);
	printf("Something went wrong\n");
	printf(MSG);
	return (INVALID);
}

t_exit	good_exit(t_etq *e)
{
	laundry(e);
	return (VALID);
}
