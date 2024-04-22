/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 16:01:41 by arybarsk          #+#    #+#             */
/*   Updated: 2024/01/01 16:01:46 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	count;

	count = 0;
	while (*str)
	{
		str++;
		count++;
	}
	return (count);
}

void	write_usage_msg(void)
{
	const char	*msg
		= "USAGE:\n"
		"./philo <number_of_philosophers>\n"
		"<time_to_die> <time_to_eat> <time_to_sleep>\n"
		"(optional)<number_of_times_each_philosopher_must_eat>\n";

	write(2, msg, ft_strlen(msg) - 1);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc == 5 || argc == 6)
	{
		set_empty_sim(&sim);
		if (set_simulation(&sim, argv) < 0)
		{
			printf("Error: invalid input\n");
			return (-1);
		}
		sim.is_stopped = false;
		sim.sim_start = go_get_time();
		set_threads(&sim);
		while (!sim.is_stopped && !has_one_died(&sim)
			&& !have_all_eaten_enough(&sim))
			usleep (1000);
		leave_like_a_boss(&sim);
		return (0);
	}
	else
	{
		write_usage_msg();
		return (1);
	}
}
