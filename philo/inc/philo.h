/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acuva-nu <acuva-nu@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 20:37:25 by acuva-nu          #+#    #+#             */
/*   Updated: 2023/12/05 14:55:11 by acuva-nu         ###   ########.fr       */
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
# include <limits.h>
/**/

typedef struct s_philo
{
	unsigned int					id;
	unsigned int					forks[2];
	pthread_mutex_t		eating;
	unsigned int					nb_meals;
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
	int 				stop_flag;
	pthread_t			checker;
	long long			start_time;
	pthread_mutex_t		*forks;
	pthread_mutex_t     check;
	pthread_mutex_t		print;
	t_philo				*philos;
}						t_etiquette;
/**/
typedef enum e_status
{
	FORK1,
	FORK2,
	DEAD,
	THINK,
	EAT,
	SLEEP,
	DEBUG
}						t_status;

int is_flag_on(t_etiquette *e);
void set_stop_flag(t_etiquette *e, int flag);

void equal_start(long long time);
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

/*-----------------UTILS--------------------*/
/*@brief Converts the string received 
 * if numeric to to numeric format type*/
int						ft_atoi(const char *str);
/*@brief returns the time in milliseconds*/
long long				get_timestamp();
/*Return logs the status for 
 * what the philosopher is 
 * currently doing*/
void					log_status(t_philo *p,
							t_status status, int flag);
#endif
