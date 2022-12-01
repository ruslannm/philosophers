/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:59 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:54:27 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_checker_eaten_thread(t_table *table)
{
	if (table->input.number_of_times_each_philosopher_must_eat > 0)
	{
		if (pthread_create(&(table->checker_eaten), NULL, &checker_eaten, \
			(void *) table))
			return (1);
		if (pthread_detach(table->checker_eaten) != 0)
			return (1);
	}
	return (0);
}

int	create_threads(t_table *table)
{
	int	i;

	if (create_checker_eaten_thread(table))
		return (1);
	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		table->philosophers[i].proccess_id = fork();
		if (table->philosophers[i].proccess_id < 0)
		{
			while (--i >= 0)
				kill(table->philosophers[i].proccess_id, SIGKILL);
			return (1);
		}
		if (table->philosophers[i].proccess_id == 0)
		{
			process(&table->philosophers[i]);
		}
		++i;
	}
	return (0);
}

void	*process(void *args)
{
	t_philosopher	*philosopher;
	t_table			*table;

	philosopher = (t_philosopher *)args;
	table = philosopher->table;
	if (pthread_create(&(philosopher->checker_dead), NULL, &checker_dead, \
		(void *) philosopher))
		return (NULL);
	if (pthread_detach(philosopher->checker_dead) != 0)
		return (NULL);
	while (1)
	{
		if (process_execute(philosopher, table))
			break ;
	}
	return (NULL);
}

void	*checker_eaten(void *args)
{
	t_table	*table;
	int		i;

	table = (t_table *)args;
	i = -1;
	while (++i < table->input.number_of_philosophers)
	{
		sem_wait(table->enough_eaten);
		if (table->simulation_stop)
			break ;
	}
	sem_post(table->dead);
	return (NULL);
}

void	*checker_dead(void *args)
{
	t_philosopher	*philosopher;
	long long		time;

	philosopher = (t_philosopher *)args;
	while (1)
	{
		time = get_delta_time(philosopher->last_meal_time);
		if (time > philosopher->table->input.time_to_die)
		{
			ft_print(philosopher, philosopher->table, DIED);
			sem_wait(philosopher->table->writer);
			sem_post(philosopher->table->dead);
			philosopher->table->simulation_stop = 1;
			while (1)
				if (sem_post(philosopher->table->enough_eaten))
					break ;
			exit (1);
		}
	}
	return (NULL);
}
