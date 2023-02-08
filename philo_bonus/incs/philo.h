/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:01:28 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/08 16:33:51 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include "colors.h"

typedef struct s_philo
{
	pid_t			pid;
	pthread_t		death;
	int				nb;
	int				last_eat;
	int				eat_count;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	size_t				start_time;
	t_philo				*philos;
	pthread_t			check_eated;
	sem_t				*forks;
	sem_t				*eat;
	sem_t				*lock;
	sem_t				*end;
	int					nphilo;
	int					tt[4];
}						t_data;

/*-MAIN-*/
int		check_input(char **av);
int		fill_data(t_data *data);
int		create_semaphores(t_data *data);

/*-UTILS-*/
void	*check_eat(void *arg);
void	*check_end(void *arg);
void	philo_wait(int milis, t_data *data);
int		get_time(t_data *data);
int		ft_atoi(const char *str);

/*-PHILO*/
void	put_action(t_philo *info, int action);
void	take_fork(t_philo *info);
void	routine(t_philo *info);
int		philo(t_philo	*info);
int		create_philos(t_data *data);

#endif
