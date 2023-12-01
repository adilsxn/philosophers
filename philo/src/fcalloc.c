/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:16:25 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 21:30:12 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

/**
 * Allocates memory for an array of elements and initializes them to zero.
 *
 * @param ptr    Pointer to the memory block to be allocated.
 * @param count  Number of elements to allocate.
 * @param size   Size of each element in bytes.
 * @return       Pointer to the allocated memory block, or NULL if allocation fails.
 */
int fcalloc(void **ptr, size_t count, size_t size)
{
    *ptr = malloc(count * size);
    if (!*ptr)
        return (1);
    fmemset(*ptr, 0, count * size);
    return (0);
}