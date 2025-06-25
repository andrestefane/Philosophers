/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:20:11 by astefane          #+#    #+#             */
/*   Updated: 2025/06/25 16:12:14 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_config	config;
	pthread_t	monitor;

	if ((argc != 5 && argc != 6))
		return (printf("Número de argumentos incorrecto\n"), 1);
	check_args(argv);
	init_struct(&config, argv);
	init_philo(&config);
	if (config.meals_required == 0)
		return (free(config.forks), free(config.philos), 0);
	if (start_simulation(&config) != 0)
		return (1);
	if (pthread_create(&monitor, NULL, monitor_philo, &config) != 0)
		return (printf("Error: Creating pthread of monitoring\n"), 1);
	pthread_join(monitor, NULL);
	join_threads(&config);
	destroy_and_clean(&config);
}
