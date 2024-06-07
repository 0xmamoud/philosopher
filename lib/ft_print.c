/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamoud <mamoud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:03:20 by mamoud            #+#    #+#             */
/*   Updated: 2024/06/07 02:13:41 by mamoud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	long	time;

	pthread_mutex_lock(&philo->data->print);
	time = get_time() - philo->start;
	if (philo->data->dead != 1)
		printf("%ld %d %s\n", time, philo->id, str);
	pthread_mutex_unlock(&philo->data->print);
}
