/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 14:09:40 by astefane          #+#    #+#             */
/*   Updated: 2025/06/25 16:13:46 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

static void	update_meal_status(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->meal_lock);
	philo->count_meals++;
	if (philo->config->meals_required > 0
		&& philo->count_meals == philo->config->meals_required)
	{
		pthread_mutex_lock(&philo->config->done_eating_lock);
		philo->config->philos_done_eating++;
		if (philo->config->philos_done_eating == philo->config->n_of_philos)
			philo->config->finish = 1;
		pthread_mutex_unlock(&philo->config->done_eating_lock);
	}
	pthread_mutex_unlock(&philo->config->meal_lock);
}

static void	run_philo_loop(t_philo *philo)
{
	while (!philo->config->finish)
	{
		take_forks(philo);
		print_action(philo, "is thinking");
		pthread_mutex_lock(&philo->config->meal_lock);
		philo->last_meal_time = get_time_ms();
		pthread_mutex_unlock(&philo->config->meal_lock);
		print_action(philo, "is eating");
		usleep(philo->config->time_to_eat * 1000);
		update_meal_status(philo);
		release_forks(philo);
		print_action(philo, "is sleeping");
		usleep(philo->config->time_to_sleep * 1000);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->config->n_of_philos == 1)
	{
		pthread_mutex_lock(philo->l_f);
		print_action(philo, "has taken a fork");
		usleep(philo->config->time_to_die * 1000);
		pthread_mutex_unlock(philo->l_f);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(philo->config->time_to_eat * 1000 / 2);
	pthread_mutex_lock(&philo->config->meal_lock);
	philo->last_meal_time = get_time_ms();
	pthread_mutex_unlock(&philo->config->meal_lock);
	run_philo_loop(philo);
	return (NULL);
}

int	start_simulation(t_config *config)
{
	int	i;

	config->start = get_time_ms();
	i = 0;
	while (i < config->n_of_philos)
	{
		config->philos[i].last_meal_time = config->start;
		if (pthread_create(&config->philos[i].thread, NULL, philo_routine,
				&config->philos[i]) != 0)
		{
			printf("Error: pthread_create failed for philo %d\n", i + 1);
			return (1);
		}
		usleep(100);
		i++;
	}
	return (0);
}
