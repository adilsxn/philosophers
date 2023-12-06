/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:22:26 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/06 15:32:23 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_flag_on(t_etiquette *e)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&e->check);
	if (e->stop_flag == 1)
		ret = 1;
	pthread_mutex_unlock(&e->check);
	return (ret);
}

void	set_stop_flag(t_etiquette *e, int flag)
{
	pthread_mutex_lock(&e->check);
	e->stop_flag = flag;
	pthread_mutex_unlock(&e->check);
}
