/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:59:07 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/21 13:28:12 by aarrien-         ###   ########.fr       */
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

int	fill_data(t_data *data)
{
	int	i;

	i = 0;
	data->end = 0;
	data->philos = malloc(data->nphilo * sizeof(t_philo));
	while (data->nphilo > i++)
	{
		data->philos[i - 1].data = data;
		data->philos[i - 1].nb = i;
		data->philos[i - 1].eat_count = 0;
		data->philos[i - 1].last_eat = 0;
	}
	return (0);
}

int	create_semaphores(t_data *data)
{
	struct timeval	tv;

	sem_unlink("forks");
	sem_unlink("eat");
	sem_unlink("lock");
	sem_unlink("end");
	data->forks = sem_open("forks", O_CREAT, 0600, data->nphilo);
	data->eat = sem_open("eat", O_CREAT, 0600, 0);
	data->lock = sem_open("lock", O_CREAT, 0600, 0);
	data->end = sem_open("end", O_CREAT, 0600, 0);
	gettimeofday(&tv, NULL);
	data->start_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (0);
}

int	wait_end(t_data *data)
{
	int	i;

	i = 0;
	while (++i <= data->nphilo + 1)
		sem_post(data->lock);
	sem_wait(data->end);
	usleep(1000);
	i = 0;
	while (++i <= data->nphilo)
		kill(data->philos[i - 1].pid, SIGKILL);
	free(data->philos);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (printf("Invalid parameters\n"), 0);
	if (check_input(&av[1]) == 1)
		return (printf("Invalid character\n"), 0);
	if (ft_atoi(av[1]) > 250)
		return (printf("Too many philosophers"), 0);
	while (av[++i])
	{
		if (i > 1)
			data.tt[i - 2] = ft_atoi(av[i]);
		else
			data.nphilo = ft_atoi(av[i]);
	}
	if (ac == 5)
		data.tt[3] = -1;
	fill_data(&data);
	create_semaphores(&data);
	pthread_create(&data.check_eated, NULL, &check_eat, &data);
	create_philos(&data);
	wait_end(&data);
	return (0);
}
