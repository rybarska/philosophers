/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:48:11 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/03 14:48:13 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	act_lonely(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->fork_locks[philo->id - 1]);
	go_print(philo, "has taken a fork");
	usleep(philo->sim->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->sim->fork_locks[philo->id - 1]);
}

static void	act_last(t_philo *philo)
{
	lock_cutlery_last(philo);
	go_eat(philo);
	unlock_cutlery_last(philo);
	go_sleep(philo);
	go_think(philo);
}

static void	act_normal(t_philo *philo)
{
	lock_cutlery_normal(philo);
	go_eat(philo);
	unlock_cutlery_normal(philo);
	go_sleep(philo);
	go_think(philo);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->sim->num_of_philos == 1)
		return (act_lonely(philo), NULL);
	if (philo->id % 2 == 0)
		usleep(500);
	while (1)
	{
		if (philo->id == philo->sim->num_of_philos)
			act_last(philo);
		else
			act_normal(philo);
		pthread_mutex_lock(&philo->sim->dead_lock);
		if (philo->sim->is_stopped)
			return (pthread_mutex_unlock(&philo->sim->dead_lock), NULL);
		pthread_mutex_unlock(&philo->sim->dead_lock);
		pthread_mutex_lock(&philo->sim->enough_lock);
		if (philo->sim->have_eaten_enough)
			return (pthread_mutex_unlock(&philo->sim->enough_lock), NULL);
		pthread_mutex_unlock(&philo->sim->enough_lock);
		usleep(500);
	}
	return (NULL);
}
