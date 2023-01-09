/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:01:28 by aarrien-          #+#    #+#             */
/*   Updated: 2023/01/09 17:25:41 by aarrien-         ###   ########.fr       */
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
	int				status;
	struct s_philo	*right;
	struct s_philo	*left;
	int				fork;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	size_t				start_time;
	pthread_t			*p;
	t_philo				*philos;
	pthread_mutex_t		*forks;
	int					nphilo;
	int					tt[4];
	int					start;
	int					end;
}						t_data;

/*-MAIN-*/

/*-UTILS-*/
int		get_time(t_data *data);
int		ft_atoi(const char *str);

/*-PHILO*/
void	*philo(void *arg);
int		create_philos(t_data *data);

#endif
