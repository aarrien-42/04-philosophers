/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:21:24 by aarrien-          #+#    #+#             */
/*   Updated: 2023/01/10 10:04:14 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	take_fork(t_philo *info)
{
	if (info->nb % 2 != 0)
		usleep(1000);
	pthread_mutex_lock(&info->data->forks[info->right->nb - 1]);
	info->right->fork = 0;
	printf("%s%d%s %d has taken a fork\n",
		CYAN, get_time(info->data), X, info->nb);
	pthread_mutex_lock(&info->data->forks[info->left->nb - 1]);
	info->left->fork = 0;
	printf("%s%d%s %d has taken a fork\n",
		CYAN, get_time(info->data), X, info->nb);
}

int	routine(t_philo *info)
{
	take_fork(info);
	printf("%s%d%s %s%d is eating%s (%d)\n",
		CYAN, get_time(info->data), X, YELLOW, info->nb, X, info->eat_count + 1);
	usleep(info->data->tt[1] * 1000);
	info->eat_count++;
	info->right->fork = 1;
	info->left->fork = 1;
	pthread_mutex_unlock(&info->data->forks[info->right->nb - 1]);
	pthread_mutex_unlock(&info->data->forks[info->left->nb - 1]);
	printf("%s%d%s %s%d is sleeping%s\n",
		CYAN, get_time(info->data), X, RED, info->nb, X);
	usleep(info->data->tt[2] * 1000);
	printf("%s%d%s %d is thinking\n", CYAN, get_time(info->data), X, info->nb);
	return (0);
}

void	*philo(void *arg)
{
	t_philo	*info;

	info = (t_philo *)arg;
	while (info->data->end == 0)
	{
		if (info->data->start == 1 && info->eat_count < info->data->tt[3])
			routine(info);
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
			return (i);
	}
	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	data->start = 1;
	while (check_end(data) == 0)
		;
	//printf("%sSimulation finalized%s", PURPLE, X);
	/*i = 0;
	while (++i <= data->nphilo)
		if (pthread_join(data->p[i - 1], NULL) != 0)
			return (i);*/
	return (0);
}
