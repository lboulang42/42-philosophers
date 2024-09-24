/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:21:20 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/12 18:56:10 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
basic starton to get data from everywhere (avoid sending ptr as function args)
*/
t_data	*starton(void)
{
	static t_data	data;

	return (&data);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = starton();
	if (parse_philo(data, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_all(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
