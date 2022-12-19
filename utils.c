/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:37:31 by alemarti          #+#    #+#             */
/*   Updated: 2022/12/19 18:24:40 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_philo_status(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->mutex_printf);
	if (!philo->data->flag_stop)
		printf("%lld %d %s\n", \
			find_time() - philo->data->t_start, philo->id, str);
	pthread_mutex_unlock(&philo->data->mutex_printf);
}

long long	find_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	destroy_data(t_data *data)
{
	pthread_mutex_destroy(&data->mutex_printf);
	pthread_mutex_destroy(data->mutex_fork);
	free (data);
}

int	ft_error(char *str, void *ptr)
{
	int	i;

	i = 0;
	if (ptr)
		free (ptr);
	while (*(str + i))
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	return (-1);
}

int	destroy_everything(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->data->num_philos)
	{
		if (pthread_mutex_destroy(philos->data->mutex_fork + i))
			return (ft_error("Error: pthread_mutex_destroy", \
				philos->data->mutex_fork));
	}
	free(philos->data->mutex_fork);
	pthread_mutex_destroy(&philos->data->mutex_printf);
	pthread_mutex_destroy(&philos->data->mutex_data);
	free(philos->data);
	free(philos);
	return (0);
}
