/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:59:07 by aarrien-          #+#    #+#             */
/*   Updated: 2023/01/11 17:12:26 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	fill_data(t_data *data)
{
	int	i;

	i = 0;
	data->start = 0;
	data->end = 0;
	data->p = malloc(data->nphilo * sizeof(pthread_t));
	data->philos = malloc(data->nphilo * sizeof(t_philo));
	data->forks = malloc(data->nphilo * sizeof(pthread_mutex_t));
	while (data->nphilo > i++)
	{
		data->philos[i - 1].data = data;
		data->philos[i - 1].left = &data->philos[i - 1];
		data->philos[i - 1].right = &data->philos[i % data->nphilo];
		data->philos[i - 1].nb = i;
		data->philos[i - 1].eat_count = 0;
		data->philos[i - 1].last_eat = 0;
	}
	return (0);
}

void	free_all(t_data *data)
{
	free(data->p);
	free(data->philos);
	free(data->forks);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac < 5 || ac > 6)
		return (printf("Invalid parameters\n"), 0);
	if (check_input(&av[1]) != 0)
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
	create_philos(&data);
	free_all(&data);
	return (0);
}
