/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:09:40 by astefane          #+#    #+#             */
/*   Updated: 2025/06/18 17:03:54 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->config->finish)
	{
	}
}

void	start_simulation(t_config *config)
{
	int	i;

	i = 0;
	config->start = get_time_ms();
	while (i < config->n_of_philos)
	{
		if (pthread_create(&config->philos[i].thread, NULL,
				philo_routine, &config->philos[i]) != 0)
			(printf("Error creating thread%d\n", i), exit(1));
		i++;
	}
}
