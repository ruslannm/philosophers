/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosopher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 17:10:46 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:45:24 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philosopher(t_table *table, int i)
{
	table->philosophers[i].id = i + 1;
	table->philosophers[i].number_of_times_ate = 0;
	table->philosophers[i].last_meal_time = table->start_time;
	table->philosophers[i].table = table;
}

int	create_philosophers(t_table *table)
{
	int	i;

	table->philosophers = (t_philosopher *) malloc(sizeof(t_philosopher) * \
		(table->input.number_of_philosophers));
	if (table->philosophers == NULL)
		return (1);
	i = 0;
	while (i < table->input.number_of_philosophers)
	{
		init_philosopher(table, i);
		++i;
	}
	return (0);
}
