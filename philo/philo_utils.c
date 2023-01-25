/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:29:07 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/25 21:36:22 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int					i;
	int					k;
	unsigned long long	value;
	int					d;

	i = 0;
	k = 1;
	d = 0;
	value = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
			i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			k = k * -1;
	while (str[i] == '0')
			i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		value = (value * 10) + (str[i++] - '0');
		d++;
	}
	if (d > 19 || value >= 9223372036854775808ULL)
		return (-(k == 1));
	return (value * k);
}

long long int current_timestamp(void)
{
    struct timeval te; 
    gettimeofday(&te, NULL);
    long long int milliseconds;
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
    return (milliseconds);
}

int	checker_one(int ac, char **av)
{
	int i = 0;
	int j = 1;
	if(ac == 5 || ac == 6)
	{
		while (av[j])
		{
			i = 0;
			while (av[j][i])
			{
				if(av[j][i] >= '0' && av[j][i] <= '9')
					i++;
				else
					return(0);
			}
			j++;
		}
	}
	else
		return(0);
	i = 1;
	while (i < j)
	{
		if(av[i][0] == '\0')
			return(0);
		i++;
	}
	i = 2;
	while (i < j - 1)
	{
		if(ft_atoi(av[1]) > 200 || ft_atoi(av[i]) < 60)
			return(0);
		i++;
	}
	return(1);
}

void    sleeper(size_t milliseconds)
{
        size_t  start_time;

        start_time = current_timestamp();
        while (current_timestamp() - start_time < milliseconds)
                usleep(50);
}

void	pausing(t_philo *pause)
{
	long long time = current_timestamp();

	while (1)
	{
		if(current_timestamp() - time >= pause->env->time_to_eat)
			break ;
		usleep(500);
	}
}
