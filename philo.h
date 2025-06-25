/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:16:26 by astefane          #+#    #+#             */
/*   Updated: 2025/06/25 16:11:49 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_config
{
	int				n_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				meals_required;
	long			start;
	int				philos_done_eating;
	int				finish;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	done_eating_lock;

	pthread_mutex_t	*forks;
	int				forks_initialized;
	struct s_philo	*philos;
}					t_config;

typedef struct s_philo
{
	int				id;
	int				count_meals;
	long			last_meal_time;
	pthread_t		thread;
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	t_config		*config;
}					t_philo;

void				check_args(char **argv);
int					is_numeric(char *str);
int					long_atoi(const char *str);
void				init_struct(t_config *config, char **argv);
void				check_config(t_config *config, char **argv);
void				init_philo(t_config *config);
int					start_simulation(t_config *config);
long				get_time_ms(void);
void				print_action(t_philo *philo, char *msg);
void				take_forks(t_philo *philo);
void				release_forks(t_philo *philo);
void				*monitor_philo(void *arg);
void				join_threads(t_config *config);
void				destroy_and_clean(t_config *config);
void				print_config(t_config *config);
void				init_config_values(t_config *config, char **argv);

#endif