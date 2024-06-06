/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoud <mamoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:04:43 by kane              #+#    #+#             */
/*   Updated: 2024/06/06 22:18:08 by mamoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	thinking(t_philo *philo);
static void	sleeping(t_philo *philo);
static void	eating(t_philo *philo);

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 || philo->data->nb_of_philos == philo->id + 1)
		ft_usleep(1);
	while (philo->data->dead == 0)
	{
		if (philo->data->nb_of_meals != -1 && philo->nb_of_meals >= philo->data->nb_of_meals)
			break ;
		eating(philo);
		if (philo->data->dead == 1)
			break ;
		sleeping(philo);
		if (philo->data->dead == 1)
			break ;
		thinking(philo);
		if (philo->data->dead == 1)
			break ;
	}
	return (args);
}

static void	thinking(t_philo *philo)
{
	ft_print(philo, "is thinking");
}

static void	sleeping(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

static void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->nb_of_philos]);
	ft_print(philo, "has taken a fork");
	philo->eating = 1;
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal = get_time();
	philo->nb_of_meals++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(philo->data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->nb_of_philos]);
}
