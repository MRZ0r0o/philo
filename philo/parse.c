/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mradwan <mradwan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 13:46:21 by mradwan           #+#    #+#             */
/*   Updated: 2023/01/29 18:02:00 by mradwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_null(char **av, int j)
{
	int	i;

	i = 1;
	while (i < j)
	{
		if (av[i][0] == '\0' || ft_atoi(av[1]) <= 0)
			return (0);
		i++;
	}
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[2]) < 60 || \
			ft_atoi(av[3]) < 60 || ft_atoi(av[4]) < 60 || \
				(av[5] && ft_atoi(av[5]) < 1))
		return (0);
	return (1);
}

int	check_nums(int ac, char **av)
{
	int	i;
	int	j;

	j = 1;
	i = 0;
	if (ac == 5 || ac == 6)
	{
		while (av[j])
		{
			i = 0;
			while (av[j][i])
			{
				if (av[j][i] >= '0' && av[j][i] <= '9')
					i++;
				else
					return (0);
			}
			j++;
		}
	}
	else
		return (0);
	if (!check_null(av, j))
		return (0);
	return (1);
}
