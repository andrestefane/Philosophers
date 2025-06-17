/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astefane <astefane@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:28:46 by astefane          #+#    #+#             */
/*   Updated: 2025/06/17 21:04:13 by astefane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(char **argv)
{
	unsigned long	n;
	int				i;

	n = 0;
	i = 1;
	while (argv[i])
	{
		if (!is_numeric(argv[i]))
			(printf("Arguments are not numbers\n"), exit(1));
		n = long_atoi(argv[i]);
		if (n > INT_MAX)
			(printf("argument is too long\n"), exit(1));
		i++;
	}
}
