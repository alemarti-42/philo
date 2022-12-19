/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 19:25:01 by alemarti          #+#    #+#             */
/*   Updated: 2022/12/19 18:27:56 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_forks(t_philo *philo)
{
	if (philo -> id % 2 == 0)
		usleep(1000);
	pthread_mutex_lock(philo->lf);
	print_philo_status(philo, "has taken a fork");
	if (philo->lf == philo->rf)
	{
		pthread_mutex_unlock(philo->lf);
		return (1);
	}
	pthread_mutex_lock(philo->rf);
	print_philo_status(philo, "has taken a fork");
	return (0);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
}

void	philo_eats(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_philo);
	philo->ts_death = find_time() + philo->data->t_die;
	pthread_mutex_unlock(&philo->mutex_philo);
	print_philo_status(philo, "is eating");
	philo_sleep(find_time() + philo->data->t_eat, philo);
	philo->meal_count -= 1;
}

void	philo_sleep(long long ts_awake, t_philo *philo)
{
	while (find_time() < ts_awake)
	{
		if (find_time() > philo->ts_death)
		{
			trigger_stop(philo->data);
			print_philo_status(philo, "died");
			return ;
		}
		usleep(5);
	}
}
