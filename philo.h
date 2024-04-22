/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:03:28 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/01 16:03:32 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>

# define MAX_INT 2147483647
# define MIN_INT -2147483648
# define TIME_ERROR -1
# define MS_IN_SEC 1000

typedef struct s_sim	t_sim;

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	pthread_t		thread;
	time_t			last_eaten;
	t_sim			*sim;
}					t_philo;

typedef struct s_sim
{
	int				num_of_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				num_each_must_eat;
	int				created_count;
	int				joined_count;
	time_t			sim_start;
	bool			is_stopped;
	bool			have_eaten_enough;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	enough_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*fork_locks;
	int				dead_lock_initialised;
	int				enough_lock_initialised;
	int				print_lock_initialised;
	int				fork_locks_initialised;
	int				initialised_fork_count;
	t_philo			**philos;
}					t_sim;

/* clean */
void	snuff_it(t_sim *sim, char *str_msg);
void	leave_like_a_boss(t_sim *sim);
/* utils */
long	go_get_time(void);
int		have_all_eaten_enough(t_sim *sim);
int		has_one_died(t_sim *sim);
/* set */
void	set_empty_sim(t_sim *sim);
int		set_simulation(t_sim *sim, char **argv);
/* threads */
void	set_threads(t_sim *sim);
void	join_threads(t_sim *sim);
/* parse */
int		get_input_num(char *numstr);
/* routine */
void	*philo_routine(void *arg);
/* actions */
void	go_print(t_philo *philo, const char *status);
void	go_eat(t_philo *philo);
void	go_sleep(t_philo *philo);
void	go_think(t_philo *philo);
/* cutlery */
void	lock_cutlery_last(t_philo *philo);
void	unlock_cutlery_last(t_philo *philo);
void	lock_cutlery_normal(t_philo *philo);
void	unlock_cutlery_normal(t_philo *philo);

#endif
