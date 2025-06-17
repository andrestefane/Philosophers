/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:35:42 by astefane          #+#    #+#             */
/*   Updated: 2025/06/17 16:02:23 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	long_atoi(char *argv)
{
	unsigned int	n;
	unsigned int	i;

	n = 0;
	i = 0;
	while (argv[i] == ' ' || argv[i] == '\t' || argv[i] == '\n'
		|| argv[i] == '\r' || argv[i] == '\v' || argv[i] == '\f')
		i++;
	if (argv[i] == '-' || argv[i] == '+')
		i++;
	while (argv[i] >= '0' && argv[i] <= '9')
	{
		n = n * 10 + (argv[i] - '0');
		i++;
	}
	return (n);
}
