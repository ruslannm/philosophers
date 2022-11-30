/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:22:42 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 16:40:05 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_execute(t_philosopher *philosopher, t_table *table)
{
	if (eat(philosopher, table, EAT, table->input.time_to_eat))
		return (1);
	if (action(philosopher, table, SLEEP, table->input.time_to_sleep))
		return (1);
	action(philosopher, table, THINK, 0);
	return (0);
}

int	is_dead(t_table *table)
{
	long long	time;
	int			i;

	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		time = get_delta_time(table->philosophers[i].last_meal_time);
		if (time > table->input.time_to_die)
		{
			ft_print(&table->philosophers[i], table, DIED);
			table->simulation_stop = 1;
			table->philosophers[i].simulation_stop = 1;
			return (1);
		}
		++i;
	}
	return (0);
}

int	is_simulation_stop(t_table *table)
{
	int			i;
	int			number_of_philosophers_ate;

	i = 0;
	number_of_philosophers_ate = 0;
	while (i < table->input.number_of_philosophers)
	{
		if (table->philosophers[i].number_of_times_ate \
			>= table->input.number_of_times_each_philosopher_must_eat)
			++number_of_philosophers_ate;
		++i;
	}
	if (number_of_philosophers_ate == table->input.number_of_philosophers)
	{
		table->simulation_stop = 1;
		return (1);
	}
	return (0);
}

int	ft_print(t_philosopher *philosopher, t_table *table, char *state)
{
	long long	delta_time;

	if (philosopher->simulation_stop)
		return (0);
	delta_time = get_delta_time(table->start_time);
	pthread_mutex_lock(&table->writer);
	printf("%-10lld %-3d %-30s\n", delta_time, philosopher->id, state);
	pthread_mutex_unlock(&table->writer);
	return (0);
}
