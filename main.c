/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:20:11 by astefane          #+#    #+#             */
/*   Updated: 2025/06/24 17:22:30 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_config(t_config *config)
{
	printf("===== CONFIGURACIÓN DE LA SIMULACIÓN =====\n");
	printf("Número de filósofos       : %d\n", config->n_of_philos);
	printf("Tiempo hasta morir (ms)   : %ld\n", config->time_to_die);
	printf("Tiempo para comer (ms)    : %ld\n", config->time_to_eat);
	printf("Tiempo para dormir (ms)   : %ld\n", config->time_to_sleep);
	if (config->must_eat_count == -1)
		printf("Veces que debe comer c/u  : [no definido]\n");
	else
		printf("Veces que debe comer c/u  : %d\n", config->must_eat_count);
	printf("Inicio de simulación (ms) : %ld\n", config->start);
	printf("Flag de finalización      : %d\n", config->finish);
	printf("Forks                      : %p\n", (void *)config->forks);
	printf("===========================================\n");
}

int	main(int argc, char **argv)
{
	t_config	config;
	pthread_t	monitor;

	if ((argc != 5 && argc != 6) || !argc)
		return (printf("Number of argument is incorrect\n"), 0);
	check_args(argv);
	init_struct(&config, argv);
	print_config(&config);
	init_philo(&config);
	start_simulation(&config);
	if (pthread_create(&monitor, NULL, monitor_philo, &config) != 0)
		return (printf("Error: Creating pthread of monitoring\n"), 1);
	pthread_join(monitor, NULL);
	join_threads(&config);
	destroy_and_clean(&config);
}
