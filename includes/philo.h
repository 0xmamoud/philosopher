/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kane <kane@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 20:12:34 by kane              #+#    #+#             */
/*   Updated: 2024/06/06 18:59:09 by kane             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>
# include <limits.h>

# define MAX_PHILOSOPHERS 200

struct	s_data;
typedef struct s_philo
{
	int				id;
	int				nb_of_meals;
	long			start;
	long			last_meal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nb_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_of_meals;
	int				dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_mutex;
	pthread_mutex_t	dead_mutex;
	t_philo			*philos;
}	t_data;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlen(const char *s);
void	ft_usleep(long time);
long	get_time(void);

void	parsing(int ac, char **av);
int		init(t_data *data, int ac, char **av);
void	*routine(void *args);

#endif