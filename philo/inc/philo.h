/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:37:25 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/03 17:16:13 by acuva-nu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
/**/

typedef struct s_philo
{
	int					id;
	bool				full;
	pthread_mutex_t		*right_fork;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		eating;
	int					nb_meals;
	long long			meal_time;
	pthread_t			thread;
	struct s_etiquette	*rules;
}						t_philo;

typedef struct s_etiquette
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					must_eat;
	int 				stop;
	int					total_meals;
	pthread_t			checker;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t     check;
	pthread_mutex_t		print;
	t_philo				*philos;
}						t_etiquette;
/**/
typedef enum e_ph_status
{
	FORK,
	DEAD,
	THINK,
	EAT,
	SLEEP
}						t_ph_status;

int is_running(t_etiquette *e);
void stopping(t_etiquette *e);

/*ESSENTIALS*/
/*@brief Check the input arguments for 
 * correctness*/
int						argparser(int argc, char *av[]);
/*@brief initializes the main 
 * structures used by the program*/
int						set_table(t_etiquette *e, char *argv[], int argc);
/*@brief Creates and joins the threads*/
int						banquet(t_etiquette *e);
/*@brif Destroy the mutexes and free any 
 * allocated structures or arrays*/
int						laundry(t_etiquette *e);
/*@brief Routine for the dead of full
 checker responsible fot checking if the philosophers
 are dead or full*/
void					*checker(void *arg);
void					*strt_rtn(void *arg);

/*-----------ACTIONS-----------------------*/
/*@brief sleeps periodically and checks 
 * the all_alive flag for the banquet's end*/
void					_sleep(t_etiquette *e, time_t time_to_spend);

/* @brief entire lifetime of philosophers
 * eats, sleeps and thinks*/
void					life(t_philo *p, t_etiquette *e);
int						death(t_philo *p, t_etiquette *e);
void					*solo_dolo(t_etiquette *e, t_philo *p);
/*-----------------UTILS--------------------*/
/*@brief Converts the string received 
 * if numeric to to numeric format type*/
int						ft_atoi(const char *str);
/*@brief returns the time in milliseconds*/
long long				get_timestamp();
/*Return logs the status for 
 * what the philosopher is 
 * currently doing*/
void					log_status(t_philo *p, t_etiquette *e,
							t_ph_status status);
#endif
