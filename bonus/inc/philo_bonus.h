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

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	bool				full;
	int					nb_meals;
	long long			meal_time;
	pthread_t			checker;
	struct s_etiquette	*rules;
}						t_philo;

typedef struct s_etiquette
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_they_can_eat;
	bool				all_alive;
	bool				all_fed;
	int					total_meals;
	long long			start_time;
	sem_t		*forks;
	t_philo				**philos;
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
int						dth_chck(t_etiquette *e);
void					*checker(void *arg);
void					*strt_rtn(void *arg);

/*-----------ACTIONS-----------------------*/
/* @brief entire lifetime of philosophers
 * eats, sleeps and thinks*/
void					life(t_philo *p, t_etiquette *e);
int						death(t_philo *p, t_etiquette *e);
/*@brief Routine to delay the of threads with even id's */
void	delayed_start(t_philo *p); 
void					*solo_dolo(t_etiquette *e, t_philo *p);
/*-----------------UTILS--------------------*/
/*@brief Converts the string received 
 * if numeric to to numeric format type*/
int						ft_atoi(const char *str);
/*@brief returns the time in milliseconds*/
long long				get_timestamp(void);
/*Return logs the status for 
 * what the philosopher is 
 * currently doing*/
void					log_status(t_philo *p, t_etiquette *e,
							t_ph_status status);
#endif
