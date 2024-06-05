/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kane <kane@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 23:53:33 by kane              #+#    #+#             */
/*   Updated: 2024/06/06 01:15:14 by kane             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	data_input(t_data *data, int ac, char **av);
static	void	init_philos(t_data *data);

int	init(t_data *data, int ac, char **av)
{
	data_input(data, ac, av);
	data->philos = malloc(sizeof(t_philo) * data->nb_of_philos);
	if (!data->philos)
	{
		pthread_mutex_destroy(&data->print);
		pthread_mutex_destroy(&data->meal_mutex);
		pthread_mutex_destroy(&data->dead_mutex);
		return (0);
	}
	init_philos(data);
	return (1);
}

static	void	data_input(t_data *data, int ac, char **av)
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
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
}

static	void	init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].nb_of_meals = 0;
		data->philos[i].start = 0;
		data->philos[i].last_meal = 0;
		pthread_mutex_init(&data->philos[i].fork, NULL);
		i++;
	}
}
