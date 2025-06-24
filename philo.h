/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:16:26 by astefane          #+#    #+#             */
/*   Updated: 2025/06/24 17:22:48 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_config
{
	int				n_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start;
	int				finish;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	struct s_philo	*philos;
}	t_config;

typedef struct s_philo
{
	int				id;
	int				count_meals;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	t_config		*config;
}	t_philo;


void	check_args(char **argv);
long	long_atoi(char *argv);
int		is_numeric(char *str);
void	init_struct(t_config *config, char **argv);
void	check_config(t_config *config, char **argv);
void	init_philo(t_config *config);
void	start_simulation(t_config *config);
long	get_time_ms(void);
void	print_action(t_philo *philo, char *msg);
void	take_forks(t_philo *philo);
void	release_forks(t_philo *philo);
void	*monitor_philo(void *arg);
void	join_threads(t_config *config);
void	destroy_and_clean(t_config *config);

#endif