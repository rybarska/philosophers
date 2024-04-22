/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:02:03 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/01 16:02:07 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	cleanup_resources(t_sim *sim)
{
	int	i;

	if (!sim)
		return ;
	if (sim->created_count > sim->joined_count)
		join_threads(sim);
	if (sim->dead_lock_initialised)
		pthread_mutex_destroy(&sim->dead_lock);
	if (sim->enough_lock_initialised)
		pthread_mutex_destroy(&sim->enough_lock);
	if (sim->print_lock_initialised)
		pthread_mutex_destroy(&sim->print_lock);
	if (sim->fork_locks_initialised)
	{
		i = 0;
		while (i < sim->initialised_fork_count)
		{
			pthread_mutex_destroy(&sim->fork_locks[i]);
			i++;
		}
	}
}

static void	cleanup_memory(t_sim *sim)
{
	int	i;

	if (sim == NULL)
		return ;
	sim->is_stopped = true;
	if (sim->fork_locks)
		free(sim->fork_locks);
	i = 0;
	if (sim->philos)
	{
		while (i < sim->num_of_philos)
		{
			if (sim->philos[i])
				free(sim->philos[i]);
			i++;
		}
		free(sim->philos);
	}
}

void	snuff_it(t_sim *sim, char *str_msg)
{
	cleanup_resources(sim);
	cleanup_memory(sim);
	perror(str_msg);
}

void	leave_like_a_boss(t_sim *sim)
{
	cleanup_resources(sim);
	cleanup_memory(sim);
}
