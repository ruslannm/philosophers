/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:34:17 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:25:02 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	unlock_first_fork(t_table *table, int first_fork)
{
	pthread_mutex_unlock(&table->forks[first_fork]);
	pthread_mutex_unlock(&table->take_forks);
	return (1);
}

static int	take_forks(t_philosopher *philosopher, t_table *table)
{
	pthread_mutex_lock(&table->take_forks);
	pthread_mutex_lock(&table->forks[philosopher->fork.left]);
	ft_print(philosopher, table, FORK);
	if (table->input.number_of_philosophers == 1)
		return (unlock_first_fork(table, philosopher->fork.left));
	pthread_mutex_lock(&table->forks[philosopher->fork.right]);
	pthread_mutex_unlock(&table->take_forks);
	ft_print(philosopher, table, FORK);
	return (0);
}

static void	drop_forks(t_philosopher *philosopher, t_table *table)
{
	pthread_mutex_unlock(&table->forks[philosopher->fork.left]);
	pthread_mutex_unlock(&table->forks[philosopher->fork.right]);
}

int	eat(t_philosopher *philosopher, t_table *table, char *state, int time)
{
	if (take_forks(philosopher, table))
		return (1);
	philosopher->last_meal_time = get_time();
	action(philosopher, table, state, time);
	drop_forks(philosopher, table);
	++philosopher->number_of_times_ate;
	return (0);
}

int	action(t_philosopher *philosopher, t_table *table, char *state, int time)
{
	ft_print(philosopher, table, state);
	usleep(time * 1000);
	return (0);
}
