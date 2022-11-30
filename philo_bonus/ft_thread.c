/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 16:32:59 by rgero             #+#    #+#             */
/*   Updated: 2022/11/29 22:29:02 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	i;

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
			process(&table->philosophers[i], table);
		++i;
	}
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

void	process(t_philosopher *philosopher, t_table	*table)
{
	while (1)
	{
		if (process_execute(philosopher, table) || table->simulation_stop)
			break ;
	}
}

void	*checker_eaten(void *args)
{
	t_table	*table;
	int		i;

	table = (t_table *)args;
	i = -1;
	while (++i < table->input.number_of_philosophers)
		sem_wait(table->enough_eaten);
	sem_post(table->dead);
	return (NULL);
}
