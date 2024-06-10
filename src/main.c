/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:21:27 by kane              #+#    #+#             */
/*   Updated: 2024/06/10 18:00:05 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	usage(void);

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		usage();
	parsing(ac, av);
	init(&data, ac, av);
	if (data.nb_of_philos == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(data.time_to_die * 1000);
		printf("%d 1 died\n", data.time_to_die);
	}
	else
		monitoring(&data);
	cleanup(&data);
	return (0);
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

static void	usage(void)
{
	printf("Usage: ./philosopher number_of_philosophers time_to_die time_to_eat\
	time_to_sleep (optional)[number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}
