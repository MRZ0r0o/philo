/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:58:06 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/30 14:31:18 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_every_thing(t_philo **all, t_env *data)
{
	int		i;
	t_philo	*init;
	int		num;

	i = -1;
	init = *all;
	num = data->num_of_philo;
	i = -1;
	while (++i < num)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(init->env->death_lock);
	pthread_mutex_destroy(init->env->print);
	free(data->forks);
	free(data->death_lock);
	free(data->print);
	free(data);
	free(init);
}

int	lock_the_death(t_philo *life, int local)
{
	pthread_mutex_lock(life->env->death_lock);
	local = life->env->death;
	pthread_mutex_unlock(life->env->death_lock);
	return (local);
}

void	unlocks_the_forks(t_philo *life)
{
	pthread_mutex_unlock(&life->env->forks[life->left_fork]);
	pthread_mutex_unlock(&life->env->forks[life->right_fork]);
}

void	locks_the_forks(t_philo *life)
{
	pthread_mutex_lock(&life->env->forks[life->left_fork]);
	pthread_mutex_lock(&life->env->forks[life->right_fork]);
}

int	check_died(t_philo *died)
{
	int	i;
	int	time;

	i = -1;
	while (++i < died->env->num_of_philo)
	{
		pthread_mutex_lock(died->timer);
		time = current_timestamp() - died->starting - died->last_time_eat;
		pthread_mutex_unlock(died->timer);
		if (time > died->env->time_to_die)
		{
			pthread_mutex_lock(died->env->death_lock);
			died->env->death = 1;
			pthread_mutex_unlock(died->env->death_lock);
			if (died[i].num_of_epme > 0)
			{
				pthread_mutex_lock(died->env->print);
				printf("%lld %d died\n", \
					current_timestamp() - died->starting, died[i].id);
				pthread_mutex_unlock(died->env->print);
			}
			return (0);
		}
	}
	return (1);
}
