/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 20:14:57 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/03 20:14:59 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>

long	go_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (TIME_ERROR);
	return (MS_IN_SEC * (long)tv.tv_sec + (long)tv.tv_usec / MS_IN_SEC);
}

int	have_all_eaten_enough(t_sim *sim)
{
	int	i;

	if (sim->num_each_must_eat > -1)
	{
		pthread_mutex_lock(&sim->enough_lock);
		i = -1;
		while (++i < sim->num_of_philos)
		{
			if (sim ->philos[i]->times_eaten < sim->num_each_must_eat)
			{
				pthread_mutex_unlock(&sim->enough_lock);
				return (0);
			}
		}
		sim->have_eaten_enough = true;
		sim->is_stopped = true;
		pthread_mutex_unlock(&sim->enough_lock);
		return (1);
	}
	return (0);
}

int	has_one_died(t_sim *sim)
{
	int		i;
	long	time_since_eaten;

	i = -1;
	while (++i < sim->num_of_philos && !sim->is_stopped)
	{
		pthread_mutex_lock(&sim->dead_lock);
		time_since_eaten = go_get_time() - sim->philos[i]->last_eaten;
		pthread_mutex_unlock(&sim->dead_lock);
		if (time_since_eaten > sim->time_to_die)
		{
			pthread_mutex_lock(&sim->dead_lock);
			sim->is_stopped = true;
			pthread_mutex_unlock(&sim->dead_lock);
			pthread_mutex_lock(&sim->print_lock);
			printf("%ld   %d %s\n", go_get_time()
				- sim->sim_start, sim->philos[i]->id, "died");
			pthread_mutex_unlock(&sim->print_lock);
			return (1);
		}
	}
	return (0);
}
