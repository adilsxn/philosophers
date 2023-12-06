/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:57:08 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/06 15:48:12 by acuva-nu         ###   ########.fr       */
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

static int	are_valid(char **av, int ac)
{
	int	i;

	i = 0;
	while (++i < ac)
		if (arenum(av[i]) || ft_atoi(av[i]) < 0)
			return (1);
	return (0);
}

int	argparser(int argc, char *av[])
{
	if (argc < 5 || argc > 6)
	{
		printf(MSG);
		return (1);
	}
	if (are_valid(av, argc))
		return (printf("Error: non numeric or > INT_MAX\n"), 2);
	if (ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > 201 || ft_atoi(av[2]) < 0
		|| ft_atoi(av[3]) < 0 || ft_atoi(av[4]) < 0)
		return (printf("Invalid parameters!\n"), 3);
	if (av[5] && ft_atoi(av[5]) < 1)
		return (printf("Nbr times they must needs to be > 0!\n"), 4);
	return (0);
}
