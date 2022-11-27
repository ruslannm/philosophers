/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:22:42 by rgero             #+#    #+#             */
/*   Updated: 2022/11/27 20:38:29 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	process_execute(t_philosopher *philosopher)
{
	if (eat(philosopher, EAT, philosopher->table->input.time_to_eat))
		return (1);
	if (philosopher->table->input.number_of_times_each_philosopher_must_eat \
		!= philosopher->number_of_times_ate)
	{
		if (action(philosopher, SLEEP, philosopher->table->input.time_to_sleep))
			return (1);
		if (action(philosopher, THINK, 0))
			return (1);
	}
	return (0);
}

void	*process(void *args)
{
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = (t_philosopher *)args;
	table = philosopher->table;
	if (table->input.number_of_times_each_philosopher_must_eat > 0)
	{
		while (table->input.number_of_times_each_philosopher_must_eat \
			> philosopher->number_of_times_ate
			&& table->philosopher_dead == 0)
			if (process_execute(philosopher))
				break ;
	}
	else
	{
		while (table->philosopher_dead == 0)
		{
			if (process_execute(philosopher))
				break ;
		}
	}
	return (NULL);
}

static int	is_dead(t_table *table)
{
	long long	time;
	int			i;

	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		time = get_delta_time(table->philosophers[i].last_meal_time);
		if (time > table->input.time_to_die)
		{
			table->philosopher_dead = 1;
			ft_print(&table->philosophers[i], DIED);
			return (1);
		}
		++i;
	}
	return (0);
}

void	*checker(void *args)
{
	t_table	*table;
	int		i;

	table = (t_table *)args;
	i = 0;
	if (table->input.number_of_times_each_philosopher_must_eat > 0)
	{
		while (table->number_of_philosophers_ate < \
			table->input.number_of_philosophers)
			if (is_dead(table))
				break ;
	}
	else
	{
		while (1)
			if (is_dead(table))
				break ;
	}
	return (NULL);
}

int	ft_print(t_philosopher *philosopher, char *state)
{
	long long	delta_time;

	delta_time = get_delta_time(philosopher->table->start_time);
	pthread_mutex_lock(&philosopher->table->writer);
	if (philosopher->table->philosopher_dead)
	{
		if (philosopher->table->philosopher_dead == 1)
		{
			printf("%-10lld %-3d %-30s\n", delta_time, philosopher->id, state);
			philosopher->table->philosopher_dead = 2;
		}	
		pthread_mutex_unlock(&philosopher->table->writer);
		return (1);
	}
	else
	{
		printf("%-10lld %-3d %-30s\n", delta_time, philosopher->id, state);
	}
	pthread_mutex_unlock(&philosopher->table->writer);
	return (0);
}
