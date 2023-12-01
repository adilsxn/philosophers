#include "../inc/philo_bonus.h"

int	init_sem(sem_t **sem, const char *name, size_t size)
{
	sem_unlink(name);
	*sem = sem_open(name, O_CREAT, S_IRWXU, size);
	if (*sem == SEM_FAILED)
		return (1);
	return (0);
}
