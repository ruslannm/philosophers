/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:34:17 by rgero             #+#    #+#             */
/*   Updated: 2022/11/28 21:49:17 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	unlock_left_forks(t_philosopher *philosopher, t_table *table)
{
	pthread_mutex_unlock(&table->forks[philosopher->fork.left]);
	pthread_mutex_unlock(&table->take_forks);
	return (1);
}

static int	take_forks(t_philosopher *philosopher, t_table *table)
{
	if (pthread_mutex_lock(&table->take_forks) != 0)
		return (1);
	if (pthread_mutex_lock(&table->forks[philosopher->fork.left]))
		return (1);
	if (ft_print(philosopher, table, FORK))
		return (unlock_left_forks(philosopher, table));
	if (table->input.number_of_philosophers == 1)
		return (unlock_left_forks(philosopher, table));
	if (pthread_mutex_lock(&table->forks[philosopher->fork.right]))
		return (unlock_left_forks(philosopher, table));
	if (ft_print(philosopher, table, FORK))
	{
		pthread_mutex_unlock(&table->forks[philosopher->fork.left]);
		pthread_mutex_unlock(&table->forks[philosopher->fork.right]);
		pthread_mutex_unlock(&table->take_forks);
		return (1);
	}
	pthread_mutex_unlock(&table->take_forks);
	return (0);
}

static int	drop_forks(t_philosopher *philosopher, t_table *table)
{
	if (pthread_mutex_unlock(&table->forks[philosopher->fork.left]))
		return (1);
	if (pthread_mutex_unlock(&table->forks[philosopher->fork.right]))
		return (1);
	return (0);
}

int	eat(t_philosopher *philosopher, t_table *table, char *state, int time)
{
	if (take_forks(philosopher, table))
		return (1);
	philosopher->last_meal_time = get_time();
	++philosopher->number_of_times_ate;
	if (action(philosopher, table, state, time))
		return (1);
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
