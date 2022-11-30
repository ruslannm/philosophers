/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 10:19:53 by rgero             #+#    #+#             */
/*   Updated: 2022/11/30 11:27:58 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec * 0.001));
}

long long	get_delta_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

void	execute_action(long long time, t_table *table)
{
	long long	batch;
	long long	time_passed;

	if (time > 5)
	{
		batch = 5;
		time_passed = 0;
		while (time_passed <= time && table->simulation_stop == 0)
		{
			usleep(batch * 1000);
			time_passed += batch;
		}
		if (table->simulation_stop == 0)
			usleep((time_passed - time) * 1000);
	}
	else
	{
		usleep(time * 1000);
	}
}
