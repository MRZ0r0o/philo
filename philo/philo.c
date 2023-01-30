/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 02:14:33 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/30 14:30:10 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo(char **av)
{
	if (ft_atoi(av[1]) == 1)
	{
		printf("philo died\n");
		return (0);
	}
	return (1);
}

void	philo_init_helper(t_env *data, char **av)
{
	int	i;

	i = -1;
	data->death = 0;
	data->num_of_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	data->death_lock = malloc(sizeof(pthread_mutex_t));
	data->print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->death_lock, NULL);
	pthread_mutex_init(data->print, NULL);
	while (++i < data->num_of_philo)
		pthread_mutex_init(&data->forks[i], NULL);
}

void	philo_init(t_philo **tmp, char **av)
{
	int		i;
	t_env	*data;
	t_philo	*init;

	i = -1;
	*tmp = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	init = *tmp;
	init->timer = malloc(sizeof(pthread_mutex_t));
	data = malloc(sizeof(t_env));
	pthread_mutex_init(init->timer, NULL);
	philo_init_helper(data, av);
	i = -1;
	while (++i < ft_atoi(av[1]))
	{
		if (av[5])
			init[i].num_of_epme = ft_atoi(av[5]);
		if (!av[5])
			init[i].num_of_epme = INT_MAX;
		init[i].env = data;
		init[i].id = i + 1;
		init[i].left_fork = i;
		init[i].right_fork = (i + 1) % ft_atoi(av[1]);
		init[i].starting = current_timestamp();
	}
}

int	main(int ac, char **av)
{
	t_philo	*philo;
	int		i;

	if (!check_philo(av))
		return (0);
	if (!check_nums(ac, av))
	{
		printf("invalid\n");
		return (0);
	}
	philo_init(&philo, av);
	threads_creation(philo);
	while (1)
	{
		if (!check_died(philo) || philo->num_of_epme == 0)
		{
			i = -1;
			while (++i < philo->env->num_of_philo)
				pthread_join(philo[i].philo, NULL);
			free_every_thing(&philo, philo->env);
			return (0);
		}
	}
}
