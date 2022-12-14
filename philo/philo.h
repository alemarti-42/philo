/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:30:59 by alemarti          #+#    #+#             */
/*   Updated: 2022/12/21 17:46:46 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				num_philos;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_meals;
	int				flag_stop;
	int				finished;
	long long int	t_start;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_printf;
	pthread_mutex_t	mutex_data;
	pthread_t		pth_monitor_t;
}t_data;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	long long int	ts_death;
	t_data			*data;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	pthread_mutex_t	mutex_philo;
	pthread_t		pth_t;
}t_philo;

//init_philo.c
int			init_philos(t_philo **philos, int argc, char **argv);

//routine_utils.c
int			take_forks(t_philo *philo);
void		release_forks(t_philo *philo);
void		philo_eats(t_philo *philo);
void		philo_sleep(long long time);

//stop.c
void		trigger_stop(t_data *data);
int			check_stop(t_data *data);

//utils.c
void		print_philo_status(t_philo *philo, char *str);
long long	find_time(void);
void		destroy_data(t_data *data);
int			ft_error(char *str, void *ptr);
int			destroy_everything(t_philo *philos);

#endif