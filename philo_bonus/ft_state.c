/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:34:17 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 12:05:11 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philosopher *philosopher, t_table *table)
{
	if (sem_wait(&table->forks))
		return (1);
	if (ft_print(philosopher, table, FORK))
		return (sem_post(&table->forks));
	if (table->input.number_of_philosophers == 1)
		return (sem_post(&table->forks));
	if (sem_wait(&table->forks))
		return (1);
	if (ft_print(philosopher, table, FORK))
		return (sem_post(&table->forks));
	return (0);
}

static int	drop_forks(t_philosopher *philosopher, t_table *table)
{
	if (sem_post(&table->forks))
		return (1);
	if (sem_post(&table->forks))
		return (1);
	return (0);
}

int	eat(t_philosopher *philosopher, t_table *table, char *state, int time)
{
	if (take_forks(philosopher, table))
		return (1);
	philosopher->last_meal_time = get_time();
	++philosopher->number_of_times_ate;
	if (table->input.number_of_times_each_philosopher_must_eat && \
		philosopher->number_of_times_ate == \
		table->input.number_of_times_each_philosopher_must_eat)
		sem_post(table->enough_eaten);
	if (action(philosopher, table, state, time))
	{
		drop_forks(philosopher, table);
		return (1);
	}
	if (drop_forks(philosopher, table))
		return (1);
	return (0);
}

int	action(t_philosopher *philosopher, t_table *table, char *state, int time)
{
	if (ft_print(philosopher, table, state))
		return (1);
	execute_action(time);
	return (0);
}
