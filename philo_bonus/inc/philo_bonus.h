/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:37:25 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 21:42:03 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>
# include <string.h>
# include <unistd.h>

typedef pthread_t	t_th;

# define MSG "Usage:\nt./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_ph
{
	pid_t			pid;
	int				meals;
	time_t			time;
	t_th			th;
}					t_ph;

typedef enum e_exit
{
	VALID,
	INVALID,
}					t_exit;

typedef struct s_etq
{
	int				id;
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	char			*f_name;
	char			*p_name;
	char			*e_name;
	char			*c_name;
	time_t			start;
	sem_t			*sem_f;
	sem_t			*sem_p;
	sem_t			*sem_e;
	sem_t			*sem_c;
	t_th			th;
	t_ph			*philos;
}					t_etq;

typedef enum e_status
{
	FORK,
	DEAD,
	THINK,
	EAT,
	SLEEP,
	FULL,
}					t_status;


/**
 * Sets the first 'n' bytes of the memory pointed to by 's' to the 
 * specified value 'c'.
 *
 * @param s     Pointer to the memory to be filled.
 * @param c     Value to be set.
 * @param n     Number of bytes to be set.
 * @return      Pointer to the memory area 's'.
 */

void	*fmemset(void *s, int c, size_t n);

/**
 * Allocates memory for an array of elements and initializes 
 * them to zero.
 *
 * @param ptr    Pointer to the memory block to be allocated.
 * @param count  Number of elements to allocate.
 * @param size   Size of each element in bytes.
 * @return       0 on success and 1 on failure.
 */
int fcalloc(void **ptr, size_t count, size_t size);

/**
 * Frees the memory pointed to by the given pointer.
 *
 * @param ptr A double pointer to the memory to be freed.
 */

void   ffree(void **ptr);

/**
 * @brief Converts a string to an integer value.
 *
 * This function takes a string as input and converts it to an integer value.
 * The converted value is stored in the provided integer pointer.
 *
 * @param str The string to be converted.
 * @param val Pointer to store the converted integer value.
 * @return 0 on success, 1 on failure.
 */
int					fatoi(char *str, int *val);

/**
 * Initializes a named semaphore with the given name and size.
 *
 * @param sem   A pointer to a pointer to the semaphore object.
 * @param name  The name of the semaphore.
 * @param size  The size of the semaphore.
 * @return      0 on success, 1 on failure.
 */
int					init_sem(sem_t **sem, const char *name, size_t size);

/**
 * @brief Function for handling a bad exit.
 *
 * This function is responsible for handling a bad exit in the program.
 * It takes a pointer to a t_etq structure as a parameter.
 *
 * @param e Pointer to a t_etq structure.
 * @return The exit status.
 */
t_exit				bad_exit(t_etq *e);
/**
 * @brief Function for handling a good exit.
 *
 * This function is responsible for handling a good exit in the program.
 * It takes a pointer to a t_etq structure as a parameter.
 *
 * @param e Pointer to a t_etq structure.
 * @return The exit status.
 */
t_exit				good_exit(t_etq *e);

/**
 * @brief Logs the status of a philosopher.
 *
 * This function logs the status of a philosopher identified by the t_etq 
 * structure pointer 'e'.
 * The status parameter represents the current status of the philosopher.
 *
 * @param e A pointer to the t_etq structure representing the philosopher.
 * @param status The status of the philosopher.
 * @return int Returns 0 on success, 1 on failure.
 */
int					log_status(t_etq *e, t_status status);

/**
 * @brief Timer function that returns the current time in seconds.
 *
 * This function takes a pointer to a time_t variable and updates it 
 * with the current time in seconds.
 *
 * @param val Pointer to a time_t variable to store the current time.
 * @return Returns 0 on success, 1 on failure.
 */
int					timer(time_t *val);

/**
 * @brief Calculates the time spent between the start and limit time.
 *
 * This function calculates the time spent between the start and limit time
 * and updates the `e` structure with the result.
 *
 * @param e     Pointer to the `t_etq` structure to update.
 * @param start The start time.
 * @param limit The limit time.
 */
void				lapse(t_etq *e, time_t start, time_t limit);

/**
 * @brief Function that controls if the  philosopher is going 
 * to engage in gluttony.
 *
 * This function is responsible for controling if a philosopher about to
 * engage in gluttony. It takes a void pointer as an argument, which can 
 * be used to pass any necessary data to the function.
 *
 * @param arg A void pointer that can be used to pass any necessary 
 * data to the function.
 * @return A void pointer representing the result of the function.
 */
void				*gluttony(void *arg);

/**
 * @brief Function that checks if the philosopher hasn't eaten.
 * 
 * This function represents a thread that simulates a philosopher 
 * experiencing famine.
 * It takes a void pointer as an argument and returns a void pointer.
 * 
 * @param arg The argument passed to the thread.
 * @return void* The return value of the thread.
 */
void				*famine(void *arg);

/**
 * @brief Takes a fork for the philosopher.
 *
 * This function is responsible for a philosopher taking a fork.
 * It is called when a philosopher wants to eat.
 *
 * @param e The pointer to the philosopher's data structure.
 */
void				take_fork(t_etq *e);

/**
 * @brief Releases a fork.
 *
 * This function is used to release a fork after a philosopher has 
 * finished eating.
 *
 * @param e The pointer to the t_etq structure representing 
 * the philosopher.
 */
void				put_fork(t_etq *e);

/**
 * @brief Function to simulate the eating action of a philosopher.
 *
 * This function represents the eating action of a philosopher.
 * It takes a pointer to a structure of type t_etq as a parameter.
 *
 * @param e Pointer to a t_etq structure representing the philosopher.
 */
void				ph_eat(t_etq *e);

/**
 * @brief Function to simulate the sleeping action of a philosopher.
 *
 * This function represents the sleeping action of a philosopher.
 * It takes a pointer to a structure of type t_etq as a parameter.
 * 
 * @param e The pointer to the t_etq struct.
 */
void				ph_sleep(t_etq *e);

/**
 * @brief Function to simulate the thinking action of a philosopher.
 *
 * This function represents the thinking action of a philosopher.
 * It takes a pointer to a structure of type t_etq as a parameter.
 * 
 * @param e The pointer to the t_etq struct.
 */
void				ph_think(t_etq *e);

/**
 * @brief Executes the routine for a philosopher.
 *
 * This function is responsible for executing the routine for a 
 * philosopher(grab fork, eat, put fork, sleep and think).
 *
 * @param e The pointer to the t_etq structure representing the philosopher.
 */
void				routine(t_etq *e);

#endif
