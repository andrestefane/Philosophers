/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:35:42 by astefane          #+#    #+#             */
/*   Updated: 2025/06/24 18:30:18 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	spaces(const char *str)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r'
		|| *str == '\v' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			return (0);
		str++;
	}
	return (1);
}

int	long_atoi(const char *str)
{
	long	result;
	int		digit;

	result = 0;
	if (!spaces(str))
		return (-1);
	if (*str < '0' || *str > '9')
		return (-1);
	while (*str >= '0' && *str <= '9')
	{
		digit = *str - '0';
		if (result > INT_MAX / 10 || (result == INT_MAX / 10 && digit > INT_MAX
				% 10))
			return (-1);
		result = result * 10 + digit;
		str++;
	}
	if (*str != '\0')
		return (-1);
	return ((int)result);
}
