/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:21:24 by aarrien-          #+#    #+#             */
/*   Updated: 2023/01/11 13:16:04 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//FALTA: librear el heap

#include "../incs/philo.h"

void	put_action(t_philo *info, int action)
{
	int	time;

	time = get_time(info->data);
	if (action == 0 && info->data->end == 0)
		printf("%s%d%s %d has taken a fork\n", CYAN, time, X, info->nb);
	if (action == 1 && info->data->end == 0)
		printf("%s%d%s %s%d is eating%s (%d)\n", CYAN, time, X,
			YELLOW, info->nb, X, info->eat_count);
	if (action == 2 && info->data->end == 0)
		printf("%s%d%s %s%d is sleeping%s\n", CYAN, time, X, RED, info->nb, X);
	if (action == 3 && info->data->end == 0)
		printf("%s%d%s %d is thinking\n", CYAN, time, X, info->nb);
	if (action == 4 && info->data->end == 0)
	{
		info->data->end = 1;
		printf("%s%d%s %d died\n", CYAN, time, X, info->nb);
	}
}

void	take_fork(t_philo *info)
{
	if (info->nb % 2 != 0)
		usleep(1000);
	pthread_mutex_lock(&info->data->forks[info->right->nb - 1]);
	put_action(info, 0);
	pthread_mutex_lock(&info->data->forks[info->left->nb - 1]);
	put_action(info, 0);
}

void	routine(t_philo *info)
{
	take_fork(info);
	info->last_eat = get_time(info->data);
	info->eat_count++;
	put_action(info, 1);
	philo_wait(info->data->tt[1], info->data);
	pthread_mutex_unlock(&info->data->forks[info->right->nb - 1]);
	pthread_mutex_unlock(&info->data->forks[info->left->nb - 1]);
	usleep(100);
	if (info->data->tt[3] == -1 || info->eat_count != info->data->tt[3])
		put_action(info, 2);
	philo_wait(info->data->tt[2], info->data);
	put_action(info, 3);
}

void	*philo(void *arg)
{
	t_philo	*info;

	info = (t_philo *)arg;
	while (1)
	{
		if (info->data->end == 0 && info->data->start == 1 && \
			(info->eat_count < info->data->tt[3] || info->data->tt[3] == -1))
			routine(info);
		usleep(1000);
	}
	return (0);
}

int	create_philos(t_data *data)
{
	struct timeval	tv;
	int				i;

	i = 0;
	while (++i <= data->nphilo)
	{
		if (pthread_mutex_init(&data->forks[i - 1], NULL) != 0)
			return (1);
		if (pthread_create(&data->p[i - 1], NULL,
				&philo, &data->philos[i - 1]) != 0)
			return (1);
	}
	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	data->start = 1;
	while (check_end(data) == 0)
		;
	return (0);
}
