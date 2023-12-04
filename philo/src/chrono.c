/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chrono.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 12:38:17 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/04 17:34:26 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	_sleep(t_etiquette *e, time_t time_to_spend)
{
	long long tmp;

	tmp = get_timestamp() + time_to_spend;

	while (get_timestamp() < tmp)
	{
		if (is_flag_on(e) == 1)
			break ;
		usleep(100);
	}
}

void equal_start(long long time)
{
	while (get_timestamp() < time)
		continue;
}