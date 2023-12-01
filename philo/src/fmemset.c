/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmemset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:17:26 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 20:53:59 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*fmemset(void *s, int c, size_t n)
{
    while (n--)
        ((unsigned char *)s)[n] = (unsigned char)c;
    return (s);
}