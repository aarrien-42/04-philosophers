/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 10:21:24 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/21 13:51:36 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//FALTA: librear el heap

#include "../incs/philo.h"

void	put_action(t_philo *info, int action)
{
	int	time;

	time = get_time(info->data);
	sem_wait(info->data->lock);
	if (action == 0)
		printf("%s%d%s %d has taken a fork\n", CYAN, time, X, info->nb);
	if (action == 1)
		printf("%s%d%s %s%d is eating%s (%d)\n", CYAN, time, X,
			YELLOW, info->nb, X, info->eat_count);
	if (action == 2)
		printf("%s%d%s %s%d is sleeping%s\n", CYAN, time, X, RED, info->nb, X);
	if (action == 3)
		printf("%s%d%s %d is thinking\n", CYAN, time, X, info->nb);
	sem_post(info->data->lock);
}

void	take_fork(t_philo *info)
{
	if (info->nb % 2 != 0)
		usleep(1000);
	sem_wait(info->data->forks);
	put_action(info, 0);
	sem_wait(info->data->forks);
	put_action(info, 0);
}

void	routine(t_philo *info)
{
	take_fork(info);
	info->last_eat = get_time(info->data);
	info->eat_count++;
	if (info->data->tt[3] >= 0 && info->eat_count == info->data->tt[3])
		sem_post(info->data->eat);
	put_action(info, 1);
	philo_wait(info->data->tt[1], info->data);
	sem_post(info->data->forks);
	sem_post(info->data->forks);
	usleep(2000);
	if (info->data->tt[3] == -1 || info->eat_count != info->data->tt[3])
		put_action(info, 2);
	philo_wait(info->data->tt[2], info->data);
	put_action(info, 3);
}

int	philo(t_philo	*info)
{
	info->data->start_time += get_time(info->data);
	while (1)
		routine(info);
	exit(0);
}

int	create_philos(t_data *data)
{
	pid_t			pid;
	int				i;

	i = 0;
	while (++i <= data->nphilo)
	{
		pid = fork();
		if (pid == 0)
		{
			pthread_create(&data->philos[i - 1].death, NULL,
				&check_end, &data->philos[i - 1]);
			sem_wait(data->lock);
			philo(&data->philos[i - 1]);
			exit(0);
		}
		data->philos[i - 1].pid = pid;
	}
	return (0);
}
