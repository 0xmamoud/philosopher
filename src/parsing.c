/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkane <mkane@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 23:06:16 by kane              #+#    #+#             */
/*   Updated: 2024/06/10 17:58:32 by mkane            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_error_msg(int index)
{
	if (index == 1)
		write(2, "number of philosophers must be greater than 0\n", 45);
	else if (index == 2)
		write(2, "time to die must be greater than 0\n", 35);
	else if (index == 3)
		write(2, "time to eat must be greater than 0\n", 35);
	else if (index == 4)
		write(2, "time to sleep must be greater than 0\n", 37);
	else if (index == 5)
		write(2, "number of meals must be greater or equal to 0\n", 47);
	else if (index == 0)
		write(2, "number of philosophers must be less than 200\n", 46);
	exit(1);
}

void	parsing(int ac, char **av)
{
	int	i;

	i = 1;
	if (ft_atoi(av[1]) > 200)
		ft_error_msg(0);
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
			ft_error_msg(i);
		i++;
	}
}
