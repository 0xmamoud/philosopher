/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoud <mamoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 23:53:33 by kane              #+#    #+#             */
/*   Updated: 2024/06/07 00:59:36 by mamoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	init_data_input(t_data *data, int ac, char **av);
static	int		init_philos(t_data *data);
static	int		init_mutexes(t_data *data);

void	init(t_data *data, int ac, char **av)
{
	init_data_input(data, ac, av);
	if (!init_philos(data))
		exit(0);
	if (!init_mutexes(data))
	{
		free(data->philos);
		exit(0);
	}
}

static	void	init_data_input(t_data *data, int ac, char **av)
{
	data->nb_of_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->nb_of_meals = ft_atoi(av[5]);
	else
		data->nb_of_meals = -1;
	data->dead = 0;
	data->stop = 0;
}
static	int	init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = ft_calloc(data->nb_of_philos, sizeof(t_philo));
	if (!data->philos)
		return (0);
	while (i < data->nb_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].nb_of_meals = 0;
		data->philos[i].start = get_time();
		data->philos[i].last_meal = get_time();
		data->philos[i].eating = 0;
		data->philos[i].data = data;
		i++;
	}
	return (1);	
}

static	int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = ft_calloc(data->nb_of_philos, sizeof(pthread_mutex_t));
	if (!data->forks)
		return (0);
	while (i < data->nb_of_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	return (1);
}

