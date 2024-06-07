/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoud <mamoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:05:58 by kane              #+#    #+#             */
/*   Updated: 2024/06/07 03:25:49 by mamoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *data);
static	int	check_death(t_data *data);
static	int	check_all_total_meals(t_data *data);
static int	join_threads(t_data *data);

void	monitoring(t_data *data)
{
	if (!create_threads(data))
	{
		printf("Error: failed to create threads\n");
		return ;
	}
	while (1)
	{
		if (check_death(data) || check_all_total_meals(data))
			break ;
	}
	if (!join_threads(data))
	{
		printf("Error: failed to join threads\n");
		return ;
	}
}

static int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		// if (pthread_create(&data->philos[i].thread, NULL, \
		// 	routine, &data->philos[i]))
		// {
		// 	printf("Error: failed to create thread\n");
		// 	return (0);
		// }
		pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]);
		i++;
	}
	return (1);
}

static int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (get_time() - philo->last_meal > philo->data->time_to_die && !philo->eating)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (0);
}

static	int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (is_dead(&data->philos[i]))
		{
			ft_print(&data->philos[i], "died");
			pthread_mutex_lock(&data->dead_mutex);
			data->dead++;
			pthread_mutex_unlock(&data->dead_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

static	int	check_all_total_meals(t_data *data)
{
	int	i;
	int	meals;

	if (data->nb_of_meals == -1)
		return (0);
	i = 0;
	meals = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->philos[i].nb_of_meals >= data->nb_of_meals)
			meals++;
		pthread_mutex_unlock(&data->meal_mutex);
		i++;
	}
	if (meals == data->nb_of_philos)
	{
		pthread_mutex_lock(&data->dead_mutex);
		data->dead++;
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	return (0);
}

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		// if (pthread_join(data->philos[i].thread, NULL))
		// 	return (0);
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (1);
}
