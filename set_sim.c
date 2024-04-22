/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 20:14:03 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/01 20:14:06 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_empty_sim(t_sim *sim)
{
	sim->num_of_philos = 0;
	sim->time_to_die = 0;
	sim->time_to_eat = 0;
	sim->time_to_sleep = 0;
	sim->num_each_must_eat = -1;
	sim->created_count = 0;
	sim->joined_count = 0;
	sim->sim_start = 0;
	sim->is_stopped = true;
	sim->have_eaten_enough = false;
	sim->dead_lock_initialised = 0;
	sim->enough_lock_initialised = 0;
	sim->print_lock_initialised = 0;
	sim->fork_locks_initialised = 0;
	sim->initialised_fork_count = 0;
	sim->philos = NULL;
}

static void	set_fork_locks(t_sim *sim)
{
	int	i;

	sim->fork_locks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* sim->num_of_philos);
	if (!sim->fork_locks)
		snuff_it(sim, "Error allocating memory");
	i = 0;
	while (i < sim->num_of_philos)
	{
		if (pthread_mutex_init(&sim->fork_locks[i], NULL) != 0)
			snuff_it(sim, "Error initialising fork locks");
		sim->fork_locks_initialised = 1;
		sim->initialised_fork_count = i;
		i++;
	}
}

static void	set_philos(t_sim *sim)
{
	int	i;

	sim->philos = (t_philo **)malloc(sizeof(t_philo *) * sim->num_of_philos);
	if (!sim->philos)
		snuff_it(sim, "Error allocating memory");
	i = -1;
	while (++i < sim->num_of_philos)
	{
		sim->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		if (!sim->philos[i])
			snuff_it(sim, "Error allocating memory");
		sim->philos[i]->id = i + 1;
		sim->philos[i]->times_eaten = 0;
		sim->philos[i]->last_eaten = go_get_time();
		sim->philos[i]->sim = sim;
	}
}

static int	parse_args(t_sim *sim, char **argv)
{
	if (get_input_num(argv[1]) < 0)
		return (-1);
	sim->num_of_philos = get_input_num(argv[1]);
	if (get_input_num(argv[2]) < 0)
		return (-1);
	sim->time_to_die = get_input_num(argv[2]);
	if (get_input_num(argv[3]) < 0)
		return (-1);
	sim->time_to_eat = get_input_num(argv[3]);
	if (get_input_num(argv[4]) < 0)
		return (-1);
	sim->time_to_sleep = get_input_num(argv[4]);
	if (argv[5])
	{
		if (get_input_num(argv[5]) < 0)
			return (-1);
		sim->num_each_must_eat = get_input_num(argv[5]);
	}
	return (0);
}

int	set_simulation(t_sim *sim, char **argv)
{
	if (parse_args(sim, argv) < 0)
		return (-1);
	if (sim->num_each_must_eat == 0)
		sim->have_eaten_enough = true;
	else
		sim->have_eaten_enough = false;
	if (pthread_mutex_init(&sim->dead_lock, NULL) != 0)
		snuff_it(sim, "Error initialising dead lock");
	sim->dead_lock_initialised = 1;
	if (pthread_mutex_init(&sim->enough_lock, NULL) != 0)
		snuff_it(sim, "Error initialising (eaten) enough lock");
	sim->enough_lock_initialised = 1;
	if (pthread_mutex_init(&sim->print_lock, NULL) != 0)
		snuff_it(sim, "Error initialising print lock");
	sim->print_lock_initialised = 1;
	set_fork_locks(sim);
	set_philos(sim);
	return (0);
}
