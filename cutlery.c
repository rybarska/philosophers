/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cutlery.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:42:02 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/06 15:42:05 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_cutlery_last(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->sim->num_of_philos;
	pthread_mutex_lock(&philo->sim->fork_locks[right_fork]);
	go_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->sim->fork_locks[left_fork]);
	go_print(philo, "has taken a fork");
}

void	lock_cutlery_normal(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->sim->num_of_philos;
	pthread_mutex_lock(&philo->sim->fork_locks[left_fork]);
	go_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->sim->fork_locks[right_fork]);
	go_print(philo, "has taken a fork");
}

void	unlock_cutlery_last(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->sim->num_of_philos;
	pthread_mutex_unlock(&philo->sim->fork_locks[left_fork]);
	pthread_mutex_unlock(&philo->sim->fork_locks[right_fork]);
}

void	unlock_cutlery_normal(t_philo *philo)
{
	int	left_fork;
	int	right_fork;

	left_fork = philo->id - 1;
	right_fork = (philo->id) % philo->sim->num_of_philos;
	pthread_mutex_unlock(&philo->sim->fork_locks[right_fork]);
	pthread_mutex_unlock(&philo->sim->fork_locks[left_fork]);
}
