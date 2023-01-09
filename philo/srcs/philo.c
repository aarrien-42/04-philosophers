/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:21:24 by aarrien-          #+#    #+#             */
/*   Updated: 2023/01/09 18:11:04 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	take_fork(t_philo *info) // no se coordinan bien al coger los tenedores
{
	if (info->nb % 2 == 0)
	{
		pthread_mutex_lock(&info->data->forks[info->left->nb - 1]);
		info->left->fork = 0;
		printf("%s%d%s %d has taken a fork\n", CYAN, get_time(info->data), CLOSE ,info->nb);
		pthread_mutex_lock(&info->data->forks[info->right->nb - 1]);
		info->right->fork = 0;
		printf("%s%d%s %d has taken a fork\n", CYAN, get_time(info->data), CLOSE ,info->nb);
	}
	else
	{
		pthread_mutex_lock(&info->data->forks[info->right->nb - 1]);
		info->right->fork = 0;
		printf("%s%d%s %d has taken a fork\n", CYAN, get_time(info->data), CLOSE ,info->nb);
		pthread_mutex_lock(&info->data->forks[info->left->nb - 1]);
		info->left->fork = 0;
		printf("%s%d%s %d has taken a fork\n", CYAN, get_time(info->data), CLOSE ,info->nb);
	}
}

int	routine(t_philo *info)
{
	take_fork(info);
	printf("%s%d%s %s%d is eating%s\n", CYAN, get_time(info->data), CLOSE, YELLOW, info->nb, CLOSE);
	usleep(info->data->tt[1] * 1000);
	info->right->fork = 1;
	info->left->fork = 1;
	pthread_mutex_unlock(&info->data->forks[info->right->nb - 1]);
	pthread_mutex_unlock(&info->data->forks[info->left->nb - 1]);
	printf("%s%d%s %s%d is sleeping%s\n", CYAN, get_time(info->data), CLOSE, RED, info->nb, CLOSE);
	usleep(info->data->tt[2] * 1000);
	printf("%s%d%s %d is thinking\n", CYAN, get_time(info->data), CLOSE ,info->nb);
	return (0);
}

void	*philo(void *arg)
{
	t_philo	*info;
	info = (t_philo *)arg;
	while (info->data->end == 0)
	{
		if (info->data->start == 1)
			routine(info);
	}
	return (0);
}

int	create_philos(t_data *data)
{
	struct timeval tv;
	int	i;

	i = 0;
	while (++i <= data->nphilo) // create
	{
		if (pthread_mutex_init(&data->forks[i - 1], NULL) != 0)
			return (1);
		if (pthread_create(&data->p[i - 1], NULL, &philo, &data->philos[i - 1]) != 0)
			return (i);
	}
	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	data->start = 1;
	i = 0;
	while (++i <= data->nphilo) // wait for them to finish
		if (pthread_join(data->p[i - 1], NULL) != 0)
			return (i);
	return (0);
}
