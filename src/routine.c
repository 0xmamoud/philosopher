/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoud <mamoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:04:43 by kane              #+#    #+#             */
/*   Updated: 2024/06/07 02:54:30 by mamoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	exit_listener(t_philo *philo);
static void	thinking(t_philo *philo);
static void	sleeping(t_philo *philo);
static void	eating(t_philo *philo);

void	*routine(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	if (philo->id % 2 || philo->data->nb_of_philos == philo->id + 1)
		usleep(1);
	while (!exit_listener(philo))
	{
		eating(philo);
		if (exit_listener(philo))
			break ;
		sleeping(philo);
		if (exit_listener(philo))
			break ;
		thinking(philo);
	}
	return (args);
}

static int	exit_listener(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	if (philo->data->nb_of_meals != -1 && philo->nb_of_meals >= philo->data->nb_of_meals)
		return (1);
	return (0);
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
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[(philo->id + 1) % philo->data->nb_of_philos]);
	pthread_mutex_lock(&philo->data->forks[philo->id]);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->eating = 1;
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_print(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->nb_of_meals++;
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1) % philo->data->nb_of_philos]);
}
