/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:48:26 by aarrien-          #+#    #+#             */
/*   Updated: 2023/01/09 18:09:01 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	get_time(t_data *data)
{
	int	current;
	int	extra;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	current = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time;
	extra = current % 100;
	data->start_time += extra;
	return(current - extra); // cuidado con la trampa
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
