/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 14:47:16 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 14:47:17 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	init_sem(sem_t **sem, const char *name, size_t size)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, S_IRWXU, size);
	if (*sem == SEM_FAILED)
		return (1);
	return (0);
}
