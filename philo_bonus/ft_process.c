/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:22:42 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 19:27:15 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_execute(t_philosopher *philosopher, t_table *table)
{
	if (eat(philosopher, table, EAT, table->input.time_to_eat))
		return (1);
	if (action(philosopher, table, SLEEP, table->input.time_to_sleep))
		return (1);
	if (action(philosopher, table, THINK, 0))
		return (1);
	return (0);
}

int	ft_print(t_philosopher *philosopher, t_table *table, char *state)
{
	long long	delta_time;

	delta_time = get_delta_time(table->start_time);
	sem_wait(table->writer);
	printf("%-10lld %-3d %-30s\n", delta_time, philosopher->id, state);
	sem_post(table->writer);
	return (0);
}
