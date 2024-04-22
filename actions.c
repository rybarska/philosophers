/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:31:54 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/03 18:31:57 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	go_print(t_philo *philo, const char *status)
{
	int	l_has_eaten_enough;
	int	l_is_stopped;

	pthread_mutex_lock(&philo->sim->enough_lock);
	l_has_eaten_enough = philo->sim->have_eaten_enough;
	pthread_mutex_unlock(&philo->sim->enough_lock);
	pthread_mutex_lock(&philo->sim->dead_lock);
	l_is_stopped = philo->sim->is_stopped;
	pthread_mutex_unlock(&philo->sim->dead_lock);
	if (!l_is_stopped)
	{
		pthread_mutex_lock(&philo->sim->print_lock);
		printf("%ld   %d %s\n", go_get_time()
			- philo->sim->sim_start, philo->id, status);
		pthread_mutex_unlock(&philo->sim->print_lock);
	}
}

void	go_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->dead_lock);
	philo->last_eaten = go_get_time();
	pthread_mutex_unlock(&philo->sim->dead_lock);
	pthread_mutex_lock(&philo->sim->enough_lock);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->sim->enough_lock);
	go_print(philo, "is eating");
	usleep(philo->sim->time_to_eat * 1000);
}

void	go_sleep(t_philo *philo)
{
	int	l_has_eaten_enough;
	int	l_is_stopped;

	pthread_mutex_lock(&philo->sim->enough_lock);
	l_has_eaten_enough = philo->sim->have_eaten_enough;
	pthread_mutex_unlock(&philo->sim->enough_lock);
	pthread_mutex_lock(&philo->sim->dead_lock);
	l_is_stopped = philo->sim->is_stopped;
	pthread_mutex_unlock(&philo->sim->dead_lock);
	if (!l_is_stopped && !l_has_eaten_enough)
	{
		go_print(philo, "is sleeping");
		usleep(philo->sim->time_to_sleep * 1000);
	}
}

void	go_think(t_philo *philo)
{
	int	l_has_eaten_enough;
	int	l_is_stopped;

	pthread_mutex_lock(&philo->sim->enough_lock);
	l_has_eaten_enough = philo->sim->have_eaten_enough;
	pthread_mutex_unlock(&philo->sim->enough_lock);
	pthread_mutex_lock(&philo->sim->dead_lock);
	l_is_stopped = philo->sim->is_stopped;
	pthread_mutex_unlock(&philo->sim->dead_lock);
	if (!l_is_stopped && !l_has_eaten_enough)
		go_print(philo, "is thinking");
}
