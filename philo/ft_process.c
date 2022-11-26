/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:22:42 by rgero             #+#    #+#             */
/*   Updated: 2022/11/26 18:07:46 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


static int	process_execute(t_philosopher *philosopher)
{
	printf("test %d %d %d\n", philosopher->id, philosopher->fork.left, philosopher->fork.right);
	if (eat(philosopher, EAT, philosopher->table->input.time_to_eat))
		return (1);
	
	if (philosopher->table->input.number_of_times_each_philosopher_must_eat != philosopher->number_of_times_ate)
	{
		if (action(philosopher, SLEEP, philosopher->table->input.time_to_sleep))
			return (1);
		if (action(philosopher, THINK, philosopher->table->input.time_to_sleep))
			return (1);
	}
	return (0);
}

void	*process(void *args)
{
	t_philosopher	*philosopher;
    t_table	        *table;

	printf("test d\n");
	philosopher = (t_philosopher *)args;
	printf("test d2\n");
    table = philosopher->table;
	if (table) {
		printf("%p\n", table);
	}
	printf("test d3 %d\n", table->input.number_of_times_each_philosopher_must_eat );
	if (table->input.number_of_times_each_philosopher_must_eat > 0)
	{
		while (table->input.number_of_times_each_philosopher_must_eat > philosopher->number_of_times_ate
			&& table->philosopher_dead == 0)
			if (process_execute(philosopher))
				break ;
	}
	else
	{
		printf("test %d %d %d\n", philosopher->id, philosopher->fork.left, philosopher->fork.right);
		while (table->philosopher_dead == 0)
		{
			printf("test %d %d %d\n", philosopher->id, philosopher->fork.left, philosopher->fork.right);
			if (process_execute(philosopher))
				break ;
		}
	}
	return (NULL);
}

static int	is_dead(t_philosopher *philosopher)
{
	long long	time;

	time = get_delta_time(philosopher->time_to_die);
	if (time > philosopher->table->input.time_to_die)
	{
		ft_print(philosopher, DIED);
		philosopher->table->philosopher_dead = 1;
		return (1);
	}
	return (0);
}

void	*checker(void *args)
{
	t_philosopher	*philosopher;
    t_table	        *table;

	printf("test check\n");
	philosopher = (t_philosopher *)args;
    table = philosopher->table;
	if (table->input.number_of_times_each_philosopher_must_eat > 0)
	{
		while (table->input.number_of_times_each_philosopher_must_eat > philosopher->number_of_times_ate
			&& table->philosopher_dead == 0)
			if (is_dead(philosopher))
				break ;
	}
	else
	{
		while (table->philosopher_dead == 0)
		{
			if (is_dead(philosopher))
				break ;
		}
	}
	return (NULL);
}

int	ft_print(t_philosopher *philosopher, char *state)
{
	long long	delta_time;
	delta_time = get_delta_time(philosopher->table->start_time);
	printf("test itme\n");
	pthread_mutex_lock(&philosopher->table->writer);
	if (philosopher->table->philosopher_dead)
	{
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
