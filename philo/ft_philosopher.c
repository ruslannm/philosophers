/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:10:46 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 11:24:41 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosopher(t_table *table, int i, int j)
{
	table->philosophers[i].id = i + 1;
	table->philosophers[i].number_of_times_ate = 0;
	table->philosophers[i].simulation_stop = 0;
	table->philosophers[i].last_meal_time = table->start_time;
	if (i % 2)
	{
		table->philosophers[i].fork.left = i;
		table->philosophers[i].fork.right = j;
	}
	else
	{
		table->philosophers[i].fork.left = j;
		table->philosophers[i].fork.right = i;
	}
	table->philosophers[i].table = table;
}

int	create_philosophers(t_table *table)
{
	int	i;
	int	j;

	table->philosophers = malloc(sizeof(t_philosopher) * \
		(table->input.number_of_philosophers));
	if (table->philosophers == NULL)
		return (1);
	i = 0;
	j = 1;
	while (j < table->input.number_of_philosophers)
	{
		init_philosopher(table, i, j);
		i++;
		j++;
	}
	j = 0;
	init_philosopher(table, i, j);
	return (0);
}
