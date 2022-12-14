/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alemarti <alemarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 15:42:48 by alemarti          #+#    #+#             */
/*   Updated: 2022/12/21 17:50:09 by alemarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_args(const char *str)
{
	long int	n;
	int			max_int;

	max_int = 2147483647;
	while (*str == ' ' || *str == '\f' || *str == '\n' || \
			*str == '\r' || *str == '\t' || *str == '\v')
		str++;
	n = 0;
	while (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		if (n > max_int)
			return (ft_error("Error: Non-integer number detected", NULL));
		str++;
	}
	if (*str != '\0')
		return (ft_error("Error: Non-numerical character found", NULL));
	return ((int)n);
}

static int	init_forks_mutex(t_data *data)
{
	int				i;

	data->mutex_fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
					* data->num_philos);
	if (!data->mutex_fork)
		return (ft_error("Error: Failed to malloc forks", NULL));
	i = -1;
	while (++i < data->num_philos)
	{
		if (pthread_mutex_init(data->mutex_fork + i, NULL))
			return (ft_error("Error: pthread_mutex_fork", data->mutex_fork));
	}
	return (0);
}

static int	init_data(t_data **data, int argc, char **argv)
{
	t_data	*aux;

	aux = (t_data *)malloc(sizeof(t_data));
	if (!aux)
		return (ft_error("Error: Allocating data structure", NULL));
	aux->num_philos = get_args(argv[1]);
	aux->t_die = get_args(argv[2]);
	aux->t_eat = get_args(argv[3]);
	aux->t_sleep = get_args(argv[4]);
	aux->num_meals = -2;
	aux->finished = 0;
	if (argc == 6)
		aux->num_meals = get_args(argv[5]);
	if (aux->num_philos < 1 || aux->num_philos > 100 || aux->t_die == -1 || \
		aux->t_eat == -1 || aux->t_sleep == -1 || aux->num_meals == -1)
		return (1);
	aux->flag_stop = 0;
	if (pthread_mutex_init(&aux->mutex_printf, NULL))
		return (1);
	if (init_forks_mutex(aux))
		return (1);
	if (pthread_mutex_init(&aux->mutex_data, NULL))
		return (1);
	*data = aux;
	return (0);
}

static int	init_philo(t_philo *philo, int i, \
						t_data *data, pthread_mutex_t *forks)
{
	philo->id = i + 1;
	philo->meal_count = data->num_meals;
	philo->data = data;
	if (i == 0)
	{
		philo->lf = forks + data->num_philos - 1;
		philo->rf = forks + i;
	}
	else
	{
		philo->lf = forks + i - 1;
		philo->rf = forks + i;
	}
	philo->ts_death = find_time() + philo->data->t_die;
	if (pthread_mutex_init(&philo->mutex_philo, NULL))
		return (ft_error("Error: creating data mutex.", NULL));
	return (0);
}

int	init_philos(t_philo **philos, int argc, char **argv)
{
	t_data	*data;
	t_philo	*aux;
	int		i;

	if (init_data(&data, argc, argv))
		return (ft_error("Error: init_data()", NULL));
	aux = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (!aux)
	{
		return (ft_error("Error: malloc()", aux));
	}
	i = -1;
	while (++i < data->num_philos)
		if (init_philo(aux + i, i, data, data->mutex_fork))
			return (ft_error("Error: init_philo()", NULL));
	*philos = aux;
	return (0);
}
