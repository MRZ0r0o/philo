/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:15:36 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/25 22:06:00 by mradwan          ###   ########.fr       */
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

typedef struct t_env
{
	int num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	pthread_mutex_t *forks;
}	t_env;

typedef struct t_philo
{
	int id;
	int right_fork;
	int left_fork;
	int	num_of_epme;
	long long starting;
	int last_time_eat;
	pthread_mutex_t *print;
	pthread_t philo;
	t_env *env;
}	t_philo;

int	checker_one(int ac, char **av);
int	ft_atoi(const char *str);
void	pausing(t_philo *pause);
int	check_died(t_philo *died);
void    sleeper(size_t milliseconds);
long long int current_timestamp();

#endif