/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 12:22:42 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:46:51 by rgero            ###   ########.fr       */
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

void	ft_print(t_philosopher *philosopher, t_table *table, char *state)
{
	sem_wait(table->writer);
	printf("%-10lld %-3d %-30s\n", get_delta_time(table->start_time), \
		philosopher->id, state);
	sem_post(table->writer);
}
