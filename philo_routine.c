/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:35:33 by astefane          #+#    #+#             */
/*   Updated: 2025/06/25 16:17:12 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_action(t_philo *philo, char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->config->print_lock);
	timestamp = get_time_ms() - philo->config->start;
	if (!philo->config->finish)
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->config->print_lock);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_f);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(philo->r_f);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->config->meal_lock);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->config->meal_lock);
}

void	release_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_f);
	pthread_mutex_unlock(philo->l_f);
}
