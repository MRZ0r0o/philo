/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:29:07 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/29 18:09:07 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = sign * -1;
	while (str[i] == '0')
			i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i++] - '0');
		if ((res > 2147483647 && sign == 1) || (res > 2147483648 && sign == -1))
			return (0);
	}
	return (res * sign);
}

long long int	current_timestamp(void)
{
	struct timeval	te;
	long long int	milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

void	sleeper(size_t milliseconds)
{
	size_t	start_time;

	start_time = current_timestamp();
	while (current_timestamp() - start_time < milliseconds)
		usleep(50);
}

void	pausing(t_philo *pause)
{
	long long	time;

	time = current_timestamp();
	while (1)
	{
		if (current_timestamp() - time >= pause->env->time_to_eat)
			break ;
		usleep(500);
	}
}
