/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com>    +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:37:25 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/08/06 20:37:25 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef pthread_t t_th;

#define MSG "Usage:\nt./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n"

typedef struct s_ph
{
	int					id;
	pid_t               pid;
	bool				full;
	int					nb_meals;
	long long			meal_time;
	t_th				checker;
}						t_ph;

enum e_exit
{
	VALID,
	INVALID,
} t_exit;

typedef struct s_etq
{
	int 				id;	
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	char 			  	*f_name;
	char                *p_name;
	char                *s_name;
	char                *c_name;
	bool				all_alive;
	bool				all_fed;
	long long			start;
	sem_t		        *sem_f;
    sem_t               *sem_p;
    sem_t               *sem_t;
	sem_t  				*sem_c;
	t_th   				th;
	t_ph				*philos;
}						t_etq;
/**/
typedef enum e_status
{
	FORK,
	GRAB,
	DEAD,
	THINK,
	EAT,
	SLEEP,
	FULL,
}						t_status;
/*ESSENTIALS*/
/*@brief Check the input arguments for 
 * correctness*/
int	argparser(int argc, char *av[], t_etq *e);
/*@brief initializes the main 
 * structures used by the program*/
int						set_table(t_etq *e, char *argv[], int argc);
/*@brief Creates and joins the threads*/
int						banquet(t_etq *e);
/*@brif Destroy the mutexes and free any 
 * allocated structures or arrays*/
int						laundry_proc(t_etq *e);
/*@brief Routine for the dead of full
 checker responsible fot checking if the philosophers
 are dead or full*/
//int						dth_chck(t_etq *e);
void					*checker(void *arg);
void					strt_rtn(void *arg);

/*-----------ACTIONS-----------------------*/
/* @brief entire lifetime of philosophers
 * eats, sleeps and thinks*/
void					life(t_ph *p, t_etq *e);
int						death(t_ph *p, t_etq *e);
/*@brief Routine to delay the of threads with even id's */
void	delayed_start(t_ph *p); 
void					solo_dolo(t_etq *e, t_ph *p);
/*-----------------UTILS--------------------*/
/*@brief Converts the string received 
 * if numeric to to numeric format type*/
int	ft_atoi(char *str, int *val);
/*@brief returns the time in milliseconds*/
int				timer(long long *val);
/*Return logs the status for 
 * what the philosopher is 
 * currently doing*/
void					log_status(t_ph *p, t_etq *e,
							t_ph_status status);
#endif
