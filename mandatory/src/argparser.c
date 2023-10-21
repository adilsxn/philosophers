/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:57:08 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/06 20:57:08 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	arenum(char *s)
{
	while (*s)
	{
		if (!('0' <= *s && *s <= '9'))
			return (1);
		s++;
	}
	return (0);
}

int	argparser(int argc, char *av[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage:\n");
		printf("\t./philo [number of philosophers] [time_to_die] [time_to_eat]");
		printf("[time_to_sleep] [number_of_times_each_philosophers_must_eat]\n");
		return (1);
	}
	while (--argc > 0)
		if (arenum(av[argc]))
			return (printf("Error: Non numeric argument\n"), 2);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 201 || ft_atoi(av[2]) < 0
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (printf("Invalid parameters!\n"), 3);
	if (av[5] && ft_atoi(av[5]) < 1)
		return (printf("Nbr times they must needs to be > 0!\n"), 4);
	return (0);
}
