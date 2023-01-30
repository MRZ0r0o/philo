/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routien.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:34:51 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/30 14:30:51 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *life)
{
	pthread_mutex_lock(life->env->print);
	printf("%lld philo number %d is sleeping \n", \
		current_timestamp() - life->starting, life->id);
	pthread_mutex_unlock(life->env->print);
	sleeper(life->env->time_to_sleep);
}

void	thinking(t_philo *life)
{
	pthread_mutex_lock(life->env->print);
	printf("%lld philo number %d is thinking \n", \
		current_timestamp() - life->starting, life->id);
	pthread_mutex_unlock(life->env->print);
}

void	eating(t_philo *life)
{
	pthread_mutex_lock(life->env->print);
	printf("%lld philo number %d take the right fork\n", \
		current_timestamp() - life->starting, life->id);
	printf("%lld philo number %d take the left fork\n", \
		current_timestamp() - life->starting, life->id);
	printf("%lld philo number %d is eating \n", \
		current_timestamp() - life->starting, life->id);
	pthread_mutex_unlock(life->env->print);
}

void	threads_creation(t_philo *create)
{
	int	i;

	i = -1;
	while (++i < create->env->num_of_philo)
	{
		if (i % 2 == 0)
		{
			pthread_create(&create[i].philo, NULL, &routiene, &create[i]);
			usleep(130);
		}
	}
	i = -1;
	while (++i < create->env->num_of_philo)
	{
		if (i % 2 != 0)
		{
			pthread_create(&create[i].philo, NULL, &routiene, &create[i]);
			usleep(130);
		}
	}
}

void	*routiene(void *s)
{
	t_philo	*life;
	int		local;

	life = (t_philo *)s;
	local = 0;
	while (life->num_of_epme != 0)
	{
		locks_the_forks(life);
		if (lock_the_death(life, local))
			return (unlocks_the_forks(life), NULL);
		eating(life);
		pthread_mutex_lock(life->timer);
		life->last_time_eat = current_timestamp() - life->starting;
		pthread_mutex_unlock(life->timer);
		pausing(life);
		unlocks_the_forks(life);
		if (lock_the_death(life, local))
			return (NULL);
		sleeping(life);
		if (lock_the_death(life, local))
			return (NULL);
		thinking(life);
		life->num_of_epme--;
	}
	return (NULL);
}
