/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:02:54 by astefane          #+#    #+#             */
/*   Updated: 2025/06/25 16:13:49 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_philo_death(t_config *config, int i)
{
	long	elapsed;

	pthread_mutex_lock(&config->meal_lock);
	elapsed = get_time_ms() - config->philos[i].last_meal_time;
	if (elapsed > config->time_to_die)
	{
		pthread_mutex_unlock(&config->meal_lock);
		pthread_mutex_lock(&config->print_lock);
		printf("%ld %d died\n", get_time_ms() - config->start,
			config->philos[i].id);
		config->finish = 1;
		pthread_mutex_unlock(&config->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&config->meal_lock);
	return (0);
}

void	*monitor_philo(void *arg)
{
	t_config	*config;
	int			i;

	config = (t_config *)arg;
	while (!config->finish)
	{
		i = 0;
		while (i < config->n_of_philos)
		{
			if (check_philo_death(config, i))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (NULL);
}

void	join_threads(t_config *config)
{
	int	i;

	if (!config->philos)
		return ;
	i = 0;
	while (i < config->n_of_philos)
	{
		if (config->philos[i].thread)
			pthread_join(config->philos[i].thread, NULL);
		i++;
	}
}

void	destroy_and_clean(t_config *config)
{
	int	i;

	if (config->forks)
	{
		i = 0;
		while (i < config->forks_initialized)
		{
			pthread_mutex_destroy(&config->forks[i]);
			i++;
		}
		free(config->forks);
		config->forks = NULL;
	}
	pthread_mutex_destroy(&config->print_lock);
	pthread_mutex_destroy(&config->meal_lock);
	pthread_mutex_destroy(&config->done_eating_lock);
	if (config->philos)
	{
		free(config->philos);
		config->philos = NULL;
	}
}
