/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:48:26 by aarrien-          #+#    #+#             */
/*   Updated: 2023/01/10 10:04:58 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	check_input(char **av)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (av[j])
	{
		while (av[j][i])
		{
			if (av[j][i] >= '0' && av[j][i] <= '9')
				i++;
			else
				return (1);
		}
		i = 0;
		j++;
	}
	return (0);
}

int	check_end(t_data *data)
{
	int			i;
	static int	philo_eat;

	i = 0;
	philo_eat = 0;
	while (i < data->nphilo)
	{
		if (data->philos[i].eat_count == data->tt[3])
			philo_eat++;
		i++;
	}
	if (philo_eat == data->nphilo || data->end != 0)
		return (1);
	return (0);
}

int	get_time(t_data *data)
{
	int				current;
	int				extra;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time;
	extra = current % 100;
	data->start_time += extra;
	return (current - extra); // cuidado con la trampa
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (str[i] && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' \
	|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (num * sign);
}
