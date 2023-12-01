#include "../inc/philo_bonus.h"

int	timer(long long *val)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (1);
	*val = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	return (0);
}

void	lapse(t_etq *e, time_t start, time_t limit)
{
	long long tmp;

    if (!start)
        if (!timer(&start))
            sem_post(e->sem_t);


	while (1)
	{
		if (!timer(&tmp))
            sem_post(e->sem_t);
        if (tmp - start >= limit)
            break ;
		if (usleep(100) == -1)
            sem_post(e->sem_t);
	}
}