/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:57:09 by astefane          #+#    #+#             */
/*   Updated: 2025/06/25 14:55:22 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_config(t_config *config, char **argv)
{
	if (argv[5])
		config->meals_required = (int)long_atoi(argv[5]);
	if (config->n_of_philos <= 0 || config->n_of_philos > 200)
		(printf("Error: Number of philos are incorrect\n"), exit(1));
	if (config->time_to_die < 1 || config->time_to_eat < 1
		|| config->time_to_sleep < 1)
		(printf("Error: Times have to bee bigger than 0\n"), exit(1));
	if (pthread_mutex_init(&config->print_lock, NULL) != 0
		|| pthread_mutex_init(&config->meal_lock, NULL) != 0)
		(printf("Error: Init of mutex failed\n"), exit(1));
}
