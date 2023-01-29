/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:14:33 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/25 22:06:54 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_the_args(int ac, char **av)
{
	int i;
	int	num;

	i = 1;
	if(ft_atoi(av[1]) == 1)
	{
		printf("philo died\n");
		return 0;
	}
	if (ac > 2)
	{
		while (av[i])
		{
			num = ft_atoi(av[i]);
			if (num < 0)
				return (0);
			i++;
		}
	}
	return(1);
}

int	check_died(t_philo *died)
{
	int i = -1;
	int time;
	while (++i < died->env->num_of_philo)
	{
		time = current_timestamp() - died->starting - died->last_time_eat;
		if(time > died->env->time_to_die)
		{
			if(died[i].num_of_epme > 0)
			{	
				// pthread_mutex_lock(died->print);
				printf("%lld %d died\n", current_timestamp() - died->starting, died[i].id);
				// pthread_mutex_unlock(died->print);
			}
			// pthread_mutex_unlock(&died->env->forks[died->left_fork]);
			return(0);
		}
	}
	return(1);
}

void *routiene(void *s)
{
	t_philo *rt = (t_philo *)s;
	while (rt->num_of_epme != 0)
	{
		pthread_mutex_lock(&rt->env->forks[rt->right_fork]);
		pthread_mutex_lock(&rt->env->forks[rt->left_fork]);
		// pthread_mutex_lock(rt->print);
		printf("%lld philo number %d take the right fork\n", current_timestamp() - rt->starting, rt->id);
		printf("%lld philo number %d take the left fork\n", current_timestamp() - rt->starting, rt->id);
		printf("%lld philo number %d is eating \n", current_timestamp() - rt->starting, rt->id);
		// pthread_mutex_unlock(rt->print);
		rt->last_time_eat = current_timestamp() - rt->starting;
		pausing(rt);
		pthread_mutex_unlock(&rt->env->forks[rt->left_fork]);
		pthread_mutex_unlock(&rt->env->forks[rt->right_fork]);
		// pthread_mutex_lock(rt->print);
		printf("%lld philo number %d is sleeping \n", current_timestamp() - rt->starting, rt->id);
		// pthread_mutex_unlock(rt->print);
		sleeper(rt->env->time_to_sleep);
		// pthread_mutex_lock(rt->print);
		printf("%lld philo number %d is thinking \n", current_timestamp() - rt->starting, rt->id);
		// pthread_mutex_unlock(rt->print);
		rt->num_of_epme--;
	}
	return(NULL);
}

void	philo_times(t_philo **tmp, char **av)
{
	int i = -1;
	t_env *data;
	
	t_philo *init;
	*tmp = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	init = *tmp;
	data = malloc(sizeof(t_env));
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	// init->print = malloc(sizeof(pthread_mutex_t));
	// pthread_mutex_init(init->print, NULL);
	while(++i < ft_atoi(av[1]))
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		if(av[5])
			init[i].num_of_epme = ft_atoi(av[5]);
		if(!av[5])
			init[i].num_of_epme = INT_MAX;
		init[i].env = data;
		init[i].id = i + 1;
		init[i].left_fork = i;
		init[i].right_fork = (i + 1) % ft_atoi(av[1]);
		init[i].starting = current_timestamp();
	}
	
}

void threads_creation(t_philo *create)
{
	int i;
	
	i = -1;
	while(++i < create->env->num_of_philo)
	{
		if(i % 2 == 0)
		{
			pthread_create(&create[i].philo, NULL, &routiene, &create[i]);
			usleep(130);
		}
	}
	i = -1;
	while(++i < create->env->num_of_philo)
	{
		if(i % 2 != 0)
		{
			pthread_create(&create[i].philo, NULL, &routiene, &create[i]);
			usleep(130);
		}
	}
}

int	main(int ac, char **av)
{
	t_philo *philo;
	if (!checker_one(ac, av) || !check_the_args(ac, av))
	{
		printf("invalid\n");
		return (0);
	}
	philo_times(&philo, av);
	threads_creation(philo);
	while (1)
	{
		if(!check_died(philo))
		{
			// free(philo);
			return(0);
		}
	}
}


// i = -1;
	// while(++i < data->num_of_philo)
	// 	pthread_create(&init[i].philo, NULL, &routiene, &init[i]);
	// i = -1;
	// while (++i < data->num_of_philo)
	// 	pthread_join(init[i].philo, NULL);
	// printf("%d\n", mails);
	// i = -1;
	// while(++i < init->env->num_of_philo)
	// {
	// 	if(i % 2 == 0)
	// 	{
	// 		pthread_create(&init[i].philo, NULL, &routiene, &init[i]);
	// 		usleep(130);
	// 	}
	// }
	// i = -1;
	// while(++i < init->env->num_of_philo)
	// {
	// 	if(i % 2 == 0)
	// 	{
	// 		pthread_create(&init[i].philo, NULL, &routiene, &init[i]);
	// 		usleep(130);
	// 	}
	// }




















































// void *routiene(void *s)
// {
// 	t_philo *rt = (t_philo *)s;
// 	int local = 0;
// 	while (rt->num_of_epme != 0)
// 	{	
// 		pthread_mutex_lock(&rt->env->forks[rt->left_fork]);
// 		pthread_mutex_lock(&rt->env->forks[rt->right_fork]);

// 		pthread_mutex_lock(rt->env->death_lock);
// 		local = rt->env->death;
// 		pthread_mutex_unlock(rt->env->death_lock);
// 		if (local == 1)
// 		{
// 			pthread_mutex_unlock(&rt->env->forks[rt->right_fork]);
// 			pthread_mutex_unlock(&rt->env->forks[rt->left_fork]);
// 			return (NULL);
// 		}
			
		
// 		pthread_mutex_lock(rt->env->print);
// 		printf("%lld philo number %d take the right fork\n", current_timestamp() - rt->starting, rt->id);
// 		printf("%lld philo number %d take the left fork\n", current_timestamp() - rt->starting, rt->id);
// 		printf("%lld philo number %d is eating \n", current_timestamp() - rt->starting, rt->id);
// 		pthread_mutex_unlock(rt->env->print);
		
// 		rt->last_time_eat = current_timestamp() - rt->starting;
// 		pausing(rt);
		
// 		pthread_mutex_unlock(&rt->env->forks[rt->right_fork]);
// 		pthread_mutex_unlock(&rt->env->forks[rt->left_fork]);
		
// 		pthread_mutex_lock(rt->env->death_lock);
// 		local = rt->env->death;
// 		pthread_mutex_unlock(rt->env->death_lock);
// 		if (local == 1)
// 			return (NULL);

// 		pthread_mutex_lock(rt->env->print);
// 		printf("%lld philo number %d is sleeping \n", current_timestamp() - rt->starting, rt->id);
// 		pthread_mutex_unlock(rt->env->print);
		
// 		sleeper(rt->env->time_to_sleep);
		
// 		pthread_mutex_lock(rt->env->death_lock);
// 		local = rt->env->death;
// 		pthread_mutex_unlock(rt->env->death_lock);
// 		if (local == 1)
// 			return (NULL);

// 		pthread_mutex_lock(rt->env->print);
// 		printf("%lld philo number %d is thinking \n", current_timestamp() - rt->starting, rt->id);
// 		pthread_mutex_unlock(rt->env->print);
// 		rt->num_of_epme--;
// 	}
// 	return(NULL);
// }
