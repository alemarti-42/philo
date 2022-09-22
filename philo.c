/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:35:45 by alemarti          #+#    #+#             */
/*   Updated: 2022/09/22 22:24:35 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	printf("philo_routine:%d\n", philo->data->num_philos);
	while (!check_stop(philo->data))
	{
		//TODO: pensar, comer, dormir

		printf("philos:%d\n", philo->data->num_philos);
		take_forks(philo);
		if (check_stop(philo->data))
			break;
		philo_eats(philo);
		printf("ETED\n");
		release_forks(philo);
		if (check_stop(philo->data))
			break;
		print_philo_status(philo, "is sleeping");
		philo_sleep(find_time() + philo->data->t_sleep, philo);
	}
	printf("END routine\n");
	return (0);
}

//TODO: monitor overflows heap
static void	*monitor_routine(void *arg)
{
	t_philo *philo;
	int		i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->data->num_philos)
	{
		(philo + i)->ts_death = find_time() + philo->data->t_die;
		if (pthread_create(&(philo + i)->pth_t, NULL, &philo_routine, philo + i))
			return (0);
		i++;
	}
	while (!check_stop(philo->data))
	{
		i = 0;
		while (i < philo->data->num_philos)
		{
			if ((philo + i)->ts_death < find_time())
			{
				trigger_stop(philo->data);
				break;
			}
			i++;
		}
	}
	i = -1;
	printf("monitor routine\n");
	while (++i < philo->data->num_philos)
	{
		printf("join\n");
		//pthread_join((philo + i)->pth_t, NULL);
		printf("joined\n");
	}
	return (0);
}

//TODO: philo_start
int	monitor(t_philo *philos)
{
	//int	i;

	philos->data->t_start = find_time();
	//TODO
	if (pthread_create(&philos->data->pth_monitor_t, \
				NULL, &monitor_routine, philos))
			return (1);
	pthread_join(philos->data->pth_monitor_t, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;

	//philos = malloc(1);
	if (argc < 5 || argc > 6)
		return (ft_error("Error: Wrong number of arguments", NULL));
	if (init_philos(&philos, argc, argv))
		return (ft_error("Error: Failed to initialize philos", NULL));
	monitor(philos);
	return (0);
}