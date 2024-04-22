/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 20:25:46 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/02 20:25:48 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_threads(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->num_of_philos)
	{
		if (pthread_create(&sim->philos[i]->thread, NULL,
				&philo_routine, (void *)sim->philos[i]) != 0)
			snuff_it(sim, "Error creating philosopher threads");
		pthread_mutex_lock(&sim->print_lock);
		sim->created_count++;
		pthread_mutex_unlock(&sim->print_lock);
	}
}

void	join_threads(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->created_count)
	{
		if (pthread_join(sim->philos[i]->thread, NULL) != 0)
			snuff_it(sim, "Error joining philosopher threads");
		pthread_mutex_lock(&sim->print_lock);
		sim->joined_count++;
		pthread_mutex_unlock(&sim->print_lock);
	}
}
