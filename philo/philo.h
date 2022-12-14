/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgero <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:38:54 by rgero             #+#    #+#             */
/*   Updated: 2022/12/01 10:41:42 by rgero            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647
# define LENGTH_INT_MAX	10

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

# define USAGE "Program should take the following arguments:\n\
- number of philosophers\n\
- time to die\n\
- time to eat\n\
- time to sleep\n\
- number of times each philosopher must eat (optional)\n"

typedef struct s_table	t_table;

typedef struct s_input
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}					t_input;

typedef struct s_fork
{
	int				left;
	int				right;
}					t_fork;

typedef struct s_philosopher
{
	int				id;
	long long		last_meal_time;
	t_table			*table;
	t_fork			fork;
	pthread_t		thread_id;
	int				number_of_times_ate;
}					t_philosopher;

typedef struct s_table
{
	t_input			input;
	long long		start_time;
	int				time_to_think;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writer;
	pthread_mutex_t	take_forks;
	t_philosopher	*philosophers;
	pthread_t		checker;
}					t_table;

int					parse(int argc, char **argv, t_table *table);
int					init_table(t_table *table);
void				destroy_table(t_table *table);

int					create_philosophers(t_table *table);
int					create_forks(t_table *table);
void				ft_print(t_philosopher *philosopher, t_table *table, \
					char *state);

long long			get_time(void);
long long			get_delta_time(long long time);

int					eat(t_philosopher *philosopher, t_table *table, \
					char *state, int time);
int					action(t_philosopher *philosopher, t_table *table, \
					char *state, int time);

void				*process(void *args);
void				*checker(void *args);
int					create_threads(t_table *table);
int					process_execute(t_philosopher *philosopher, \
					t_table *table);
int					is_dead(t_table *table);
int					is_simulation_stop(t_table *table);

#endif
