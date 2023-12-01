#include "../inc/philo_bonus.h"

static void get_status(t_status status)
{
	if (status == THINK)
		printf("\033[0;36m is thinking\033[0;0m");
	if (status == EAT)
		printf("\033[0;32m is eating\033[0;0m");
	if (status == DEAD)
		printf("\033[0;31m died\033[0;0m");
	if (status == SLEEP)
		printf("\033[0;35m is sleeping\033[0;0m");
	if (status == FORK1)
		printf("\033[1;33m has taken a fork\033[0;0m");
}

int	log_status(t_etq *e, t_status status)
{

	long long tmp;

	if (sem_wait(e->sem_p) == -1 || !timer(&tmp))
		return (1);
	if (status == FULL)
		printf("\033[30;47;20m\tFinished!");
		printf("[%lld]", tmp - e->start);
	else
	{
		printf("\033[0;0m\033[1;37m\t");
		printf("%d\t", e->id + 1);
		get_status(status);
	}
	if (status == DEAD || status == FULL)
	    return (1);
	if (sem_post(e->sem_p) == -1)
		return (1);
	return (0);

}
