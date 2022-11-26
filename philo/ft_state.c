/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_state.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 14:34:17 by rgero             #+#    #+#             */
/*   Updated: 2022/11/26 17:39:24 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	take_forks(t_philosopher *philosoper)
{
    if (pthread_mutex_lock(&philosoper->table->forks[philosoper->fork.left]) != 0)
		return (1);
	if (ft_print(philosoper, FORK)){
        pthread_mutex_unlock(&philosoper->table->forks[philosoper->fork.left]);
    	return (1);
    }
	if (pthread_mutex_lock(&philosoper->table->forks[philosoper->fork.right]) != 0){
        pthread_mutex_unlock(&philosoper->table->forks[philosoper->fork.left]);
		return (1);
    }
	if (ft_print(philosoper, FORK)){
        pthread_mutex_unlock(&philosoper->table->forks[philosoper->fork.left]);
        pthread_mutex_unlock(&philosoper->table->forks[philosoper->fork.right]);
		return (1);
    }
    return (0);
}

static int	drop_forks(t_philosopher *philosoper)
{
	if (pthread_mutex_unlock(&philosoper->table->forks[philosoper->fork.left]))
		return (1);
	if (pthread_mutex_unlock(&philosoper->table->forks[philosoper->fork.right]))
		return (1);
	++philosoper->number_of_times_ate;
	return (0);
}

int	eat(t_philosopher *philosopher, char *state, int time)
{
	if (take_forks(philosopher))
		return (1);
    if (action(philosopher, state, time))
		return (1);
	if (drop_forks(philosopher))
		return (1);
	return (0);
}

int	action(t_philosopher *philosopher, char *state, int time)
{
	if (ft_print(philosopher, state))
		return (1);
	execute_action(time);
	return (0);
}




