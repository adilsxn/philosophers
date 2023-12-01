/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ffree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:16:21 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 21:40:35 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

/**
 * Frees the memory pointed to by the given pointer.
 *
 * @param ptr A double pointer to the memory to be freed.
 */

void   ffree(void **ptr)
{
    if ((*ptr && ptr))
    {
        free(*ptr);
        *ptr = NULL;
    }
}