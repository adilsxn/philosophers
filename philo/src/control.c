/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:22:26 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/03 18:13:50 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int is_running(t_etiquette *e)
{	
	int ret;

	ret = 0;
	pthread_mutex_lock(&e->check);
	if (!e->stop)
			ret = 1;
	pthread_mutex_unlock(&e->check);
		return (ret);
}

void stopping(t_etiquette *e)
{
    pthread_mutex_lock(&e->check);
    e->stop = 0;
    pthread_mutex_unlock(&e->check);
}