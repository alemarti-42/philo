/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:35:45 by alemarti          #+#    #+#             */
/*   Updated: 2022/12/21 18:22:01 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!check_stop(philo->data))
	{
		print_philo_status(philo, "is thinking");
		if (take_forks(philo) || check_stop(philo->data))
		{
			philo_sleep(find_time() + philo->data->t_die);
			break ;
		}
		philo_eats(philo);
		release_forks(philo);
		print_philo_status(philo, "is sleeping");
		if (philo->meal_count == 0)
		{
			philo->data->finished += 1;
			break ;
		}
		philo_sleep(find_time() + philo->data->t_sleep);
	}
	release_forks(philo);
	if (philo->meal_count != 0)
		philo->ts_death = 0;
	return (0);
}

static void	check_loop(t_philo *philo)
{
	int	i;

	while (!check_stop(philo->data))
	{
		i = -1;
		while (++i < philo->data->num_philos)
		{
			if ((philo + i)->ts_death < find_time() && \
				(philo + i)->meal_count != 0)
			{
				print_philo_status(philo + i, "died");
				trigger_stop(philo->data);
				return ;
			}
		}
		if (philo->data->finished >= philo->data->num_philos)
			trigger_stop(philo->data);
	}
	return ;
}

static void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->data->num_philos)
	{
		(philo + i)->ts_death = find_time() + philo->data->t_die;
		if (pthread_create(&(philo + i)->pth_t, \
			NULL, &philo_routine, philo + i))
			return (0);
		i++;
	}
	check_loop(philo);
	i = -1;
	while (++i < philo->data->num_philos)
	{
		pthread_join((philo + i)->pth_t, NULL);
	}
	return (0);
}

static int	monitor(t_philo *philos)
{
	philos->data->t_start = find_time();
	if (pthread_create(&philos->data->pth_monitor_t, \
				NULL, &monitor_routine, philos))
		return (1);
	pthread_join(philos->data->pth_monitor_t, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	if (argc < 5 || argc > 6)
		return (ft_error("Error: Wrong number of arguments", NULL));
	if (init_philos(&philos, argc, argv))
		return (ft_error("Error: init_philos()", NULL));
	if (philos->data->num_meals != 0)
		monitor(philos);
	destroy_everything(philos);
	return (0);
}
