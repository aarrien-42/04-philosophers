/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:01:28 by aarrien-          #+#    #+#             */
/*   Updated: 2023/02/21 13:21:10 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include "colors.h"

typedef struct s_philo
{
	int				nb;
	int				last_eat;
	int				eat_count;
	struct s_philo	*right;
	struct s_philo	*left;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	size_t				start_time;
	pthread_t			*p;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		lock;
	int					nphilo;
	int					tt[4];
	int					start;
	int					end;
}						t_data;

/*-MAIN-*/
int		fill_data(t_data *data);
void	free_all(t_data *data);

/*-UTILS-*/
int		check_input(char **av);
int		check_end(t_data *data);
void	philo_wait(int milis, t_data *data);
int		get_time(t_data *data);
int		ft_atoi(const char *str);

/*-PHILO*/
void	put_action(t_philo *info, int action);
void	take_fork(t_philo *info);
void	routine(t_philo *info);
void	*philo(void *arg);
int		create_philos(t_data *data);

#endif
