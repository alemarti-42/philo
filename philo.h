/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:30:59 by alemarti          #+#    #+#             */
/*   Updated: 2022/09/22 17:50:35 by alemarti         ###   ########.fr       */
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
	//int				num_forks;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_meals;
	int				flag_stop;
	//long long int	t_start;
	pthread_mutex_t	*mutex_fork;
	pthread_mutex_t	mutex_printf;
}t_data;

typedef struct s_philo
{
	int				id;
	int				meal_count;
	long long int	t_death;
	t_data			*data;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	//pthread_mutex_t	self_mutex;
	pthread_t		pth_t;
}t_philo;

int		ft_error(char *str, void *ptr);
void	destroy_data(t_data *data);


int	init_philos(t_philo **philos, int argc, char **argv);


#endif