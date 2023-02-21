/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 08:48:26 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/21 13:52:16 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	*check_eat(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (++i <= data->nphilo)
		sem_wait(data->eat);
	sem_wait(data->lock);
	sem_post(data->end);
	return (0);
}

void	*check_end(void *arg)
{
	static int	philo_eat;
	t_philo		*info;

	info = (t_philo *)arg;
	philo_eat = 0;
	while (1)
	{
		if (get_time(info->data) - info->last_eat > info->data->tt[0] || \
			(info->last_eat == 0 && get_time(info->data) > info->data->tt[0]))
		{
			sem_wait(info->data->lock);
			sem_post(info->data->end);
			printf("%s%d%s %d died\n", CYAN, get_time(info->data), X, info->nb);
			break ;
		}
	}
	return (0);
}

void	philo_wait(int milis, t_data *data)
{
	int	start;

	start = get_time(data);
	start -= start % 10;
	while (get_time(data) - start <= milis)
		usleep(50);
}

int	get_time(t_data *data)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - data->start_time);
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
