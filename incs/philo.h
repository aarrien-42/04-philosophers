/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarrien- <aarrien-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:01:28 by aarrien-          #+#    #+#             */
/*   Updated: 2022/12/28 15:46:00 by aarrien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	pthread_mutex_t	f_mutex;
	int				fork;
}					t_fork;

typedef struct s_philo
{
	int		ttd;
	int		tte;
	int		tts;
	t_fork	f;
}		t_philo;

typedef struct s_data
{
	t_philo	*philos;
	int		nphilo;
	int		g_ttd;
	int		g_tte;
	int		g_tts;
}			t_data;

#endif
