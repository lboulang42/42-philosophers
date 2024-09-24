/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 18:32:41 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/12 18:57:38 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_atoi(const char *nptr)
{
	long int	result;
	int			sign;
	int			i;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + nptr[i] - 48;
		i++;
	}
	if (result > INT_MAX)
		return (-1);
	return ((int)result);
}

/*
return (1 if str is number (positive, can start with 1 '+'));
else return (0);
*/
static int	is_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
			if (str[i] == '+')
				continue ;
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}

/*
check number of args
check for each args if number && if number is positive or == 0;
*/
static int	check_args(int ac, char **av)
{
	int	i;
	int	atoi;

	i = 0;
	if (ac < 5)
		return (printf("%s must be specified.%s is optional.\n", ARGS, NEAT),
			EXIT_FAILURE);
	if (ac > 6)
		return (printf("%s : %s must be specified.\n", ERR_TOOM, ARGS),
			EXIT_FAILURE);
	while (av[++i])
	{
		if (!is_number(av[i]))
			return (printf("%s : %s", av[i], ERR_INVAL), EXIT_FAILURE);
		atoi = ft_atoi(av[i]);
		if (atoi < 0)
			return (printf("%s : %s", av[i], ERR_INVAL), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static void	parse_args(t_data *data, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->time_die_ms = ft_atoi(av[2]);
	data->time_eat_ms = ft_atoi(av[3]);
	data->time_sleep_ms = ft_atoi(av[4]);
	if (av[5])
		data->must_eat = ft_atoi(av[5]);
	else
		data->must_eat = INT_MAX;
	data->is_dead = 0;
	data->start_ts = 0;
}

int	parse_philo(t_data *data, int ac, char **av)
{
	if (check_args(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	parse_args(data, av);
	if (data->n_philo == 0)
		return (printf("Can't run with less than 1 Philo\n"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
