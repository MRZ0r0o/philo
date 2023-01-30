/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:15:36 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/30 14:28:25 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <limits.h>

pthread_mutex_t *timing;

typedef struct t_env
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				death;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*forks;
}	t_env;

typedef struct t_philo
{
	int				id;
	int				right_fork;
	int				left_fork;
	int				num_of_epme;
	long long		starting;
	int				last_time_eat;
	pthread_mutex_t	*timer;
	pthread_t		philo;
	t_env			*env;
}	t_philo;

/*******       utils functions       ********/
int				ft_atoi(const char *str);
int				check_died(t_philo *died);
int				check_nums(int ac, char **av);
void			locks_the_forks(t_philo *life);
void			unlocks_the_forks(t_philo *life);
long long int	current_timestamp(void);
int				lock_the_death(t_philo *life, int local);

/*******       timing and routien    ********/
void			thinking(t_philo *life);
void			eating(t_philo *life);
void			sleeping(t_philo *life);
void			pausing(t_philo *pause);
void			sleeper(size_t milliseconds);

/*******       creation and freeing  ********/
void			threads_creation(t_philo *create);
void			free_every_thing(t_philo **all, t_env *data);
void			*routiene(void *s);

#endif