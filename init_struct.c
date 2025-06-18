/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:49:28 by astefane          #+#    #+#             */
/*   Updated: 2025/06/18 13:55:05 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_struct(t_config *config, char **argv)
{
	int	i;

	i = 0;
	memset(config, 0, sizeof(t_config));
	config->n_of_philos = (int)long_atoi(argv[1]);
	config->time_to_die = long_atoi(argv[2]);
	config->time_to_eat = long_atoi(argv[3]);
	config->time_to_sleep = long_atoi(argv[4]);
	config->must_eat_count = -1;
	check_config(config, argv);
	config->forks = malloc(sizeof(pthread_mutex_t) * config->n_of_philos);
	if (!config->forks)
		(printf("Error: malloc forks\n"), exit (1));
	while (i < config->n_of_philos)
	{
		if (pthread_mutex_init(&config->forks[i], NULL) != 0)
			(printf("Error: at init forks %d\n", i), exit(1));
		i++;
	}
}

void	init_philo(t_config *config)
{
	int	i;

	i = 0;
	config->philos = malloc(sizeof(t_philo) * config->n_of_philos);
	if (!config->philos)
		(printf("Error: malloc philos\n"),exit (1));
	while (i < config->n_of_philos)
	{
		config->philos[i].id = i + 1;
		config->philos[i].count_meals = 0;
		config->philos[i].last_meal_time = 0;
		config->philos[i].config = config;
		config->philos[i].l_f = &config->forks[i];
		config->philos[i].r_f = &config->forks[(i + 1) % config->n_of_philos];
		i++;
	}
}
