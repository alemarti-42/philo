/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:37:31 by alemarti          #+#    #+#             */
/*   Updated: 2022/09/22 22:15:20 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_stop(t_data *data)
{
	int	res;

	pthread_mutex_lock(&data->mutex_data);
	res = data->flag_stop;
	pthread_mutex_unlock(&data->mutex_data);
	//printf("stop:%d\n", res);
	return (res);
}

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
	//if (data->mutex_printf != 0)
		pthread_mutex_destroy(&data->mutex_printf);
	//if (data->mutex_fork == 0)
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