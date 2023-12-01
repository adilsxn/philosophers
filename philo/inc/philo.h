/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:37:25 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/01 17:30:12 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
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
typedef pthread_mutex_t t_mu;

# define MSG "Usage:\nt./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_etq
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	time_t			start;
	t_mu			*mu_f;
	t_mu			mu_p;
	t_mu			mu_e;
}					t_etq;


typedef struct s_ph
{
	int             id;
	int             left;
	int             right;
	int				meals;
	time_t			time;
	t_th            fa;
	t_th			th;
	t_ph           *e;
	
}					t_ph;

typedef enum e_exit
{
	VALID,
	INVALID,
}					t_exit;

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
 * @brief Function to handle a bad exit for a philosopher.
 * 
 * This function is responsible for handling a bad exit for a philosopher.
 * It takes a pointer to a `t_ph` structure as a parameter.
 * 
 * @param philo A pointer to a `t_ph` structure representing the philosopher.
 * @return The exit status of the function.
 */
t_exit				bad_exit(t_ph *philo);

/**
 * @brief Function to handle a good exit for a philosopher.
 * 
 * This function is responsible for handling a good exit for a philosopher.
 * It takes a pointer to a `t_ph` structure as a parameter.
 * 
 * @param philo A pointer to a `t_ph` structure representing the philosopher.
 * @return The exit status of the function.
 */
t_exit				good_exit(t_ph *philo);

/**
 * @brief Logs the status of a philosopher.
 *
 * This function logs the status of a philosopher identified by the t_ph
 * structure pointer 'e'.
 * The status parameter represents the current status of the philosopher.
 *
 * @param t_ph A pointer to the t_ph structure representing the philosopher.
 * @param status The status of the philosopher.
 * @return int Returns 0 on success, 1 on failure.
 */
int					log_status(t_ph *philo, t_status status);

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
void				lapse(t_ph *philo, time_t start, time_t limit);

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
 * @param philo The pointer to the philosopher's data structure.
 */
void				take_fork(t_ph *philo);

/**
 * @brief Releases a fork.
 *
 * This function is used to release a fork after a philosopher has 
 * finished eating.
 *
 * @param philo The pointer to the t_phstructure representing 
 * the philosopher.
 */
void				put_fork(t_ph *philo);

/**
 * @brief Function to simulate the eating action of a philosopher.
 *
 * This function represents the eating action of a philosopher.
 * It takes a pointer to a structure of type t_ph as a parameter.
 *
 * @param e Pointer to a t_phstructure representing the philosopher.
 */
void				ph_eat(t_ph *philo);

/**
 * @brief Function to simulate the sleeping action of a philosopher.
 *
 * This function represents the sleeping action of a philosopher.
 * It takes a pointer to a structure of type t_ph as a parameter.
 * 
 * @param philo The pointer to the t_ph struct.
 */
void				ph_sleep(t_ph *philo);

/**
 * @brief Function to simulate the thinking action of a philosopher.
 *
 * This function represents the thinking action of a philosopher.
 * It takes a pointer to a structure of type t_ph as a parameter.
 * 
 * @param philo The pointer to the t_ph struct.
 */
void				ph_think(t_ph *philo);


/**
 * @brief Executes the routine for a philosopher.
 *
 * This function is responsible for executing the routine of a philosopher.
 * It takes a pointer to a `t_ph` structure as a parameter.
 *
 * @param philo A pointer to a `t_ph` structure representing the philosopher.
 */
void routine(t_ph *philo);
void				routine(t_ph *philo);

#endif
