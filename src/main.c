/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kane <kane@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 22:21:27 by kane              #+#    #+#             */
/*   Updated: 2024/06/06 15:01:22 by kane             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	void	usage(void);
static	void	cleanup(t_data *data);

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5 && ac != 6)
		usage();
	parsing(ac, av);
	if (!init(&data, ac, av))
		return (0);
	printf("data initialized\n");
	cleanup(&data);
	return (0);
}

static	void	usage(void)
{
	printf("Usage: ./philosopher number_of_philosophers time_to_die time_to_eat\
	time_to_sleep (optional)[number_of_times_each_philosopher_must_eat]\n");
	exit(1);
}

static	void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].fork);
		i++;
	}
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
	free(data->philos);
}
