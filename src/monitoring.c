/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoud <mamoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:05:58 by kane              #+#    #+#             */
/*   Updated: 2024/06/06 22:13:36 by mamoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	create_threads(t_data *data);
static	void	check_death(t_data *data);
static	void	check_all_total_meals(t_data *data);
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
		check_death(data);
		if (data->dead)
			break ;
		check_all_total_meals(data);
		if (data->stop)
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
		if (pthread_create(&data->philos[i].thread, NULL, \
			routine, &data->philos[i]))
		{
			printf("Error: failed to create thread\n");
			return (0);
		}
		data->philos[i].start = get_time();
		i++;
	}
	return (1);
}

static	void	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (get_time() - data->philos[i].last_meal > data->time_to_die && \
			data->philos[i].eating == 0)
		{
			pthread_mutex_lock(&data->dead_mutex);
			ft_print(&data->philos[i], "died");
			data->dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			break ;
		}
		i++;
	}
}

static	void	check_all_total_meals(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (data->philos[i].nb_of_meals < data->nb_of_meals)
			break ;
		i++;
	}
	if (i == data->nb_of_philos)
	{
		pthread_mutex_lock(&data->stop_mutex);
		data->stop = 1;
		pthread_mutex_unlock(&data->stop_mutex);
	}
}

static int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
			return (0);
		i++;
	}
	return (1);
}
