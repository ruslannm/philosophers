/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:22:42 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:25:49 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_execute(t_philosopher *philosopher, t_table *table)
{
	if (eat(philosopher, table, EAT, table->input.time_to_eat))
		return (1);
	action(philosopher, table, SLEEP, table->input.time_to_sleep);
	action(philosopher, table, THINK, table->time_to_think);
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
		return (1);
	}
	return (0);
}

void	ft_print(t_philosopher *philosopher, t_table *table, char *state)
{
	pthread_mutex_lock(&table->writer);
	printf("%-10lld %-3d %-30s\n", get_delta_time(table->start_time), \
		philosopher->id, state);
	pthread_mutex_unlock(&table->writer);
}
