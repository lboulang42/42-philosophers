/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:55:58 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/12 19:50:05 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
printf error message specifying in which function and return exit_failure
*/
int	err(char *function, char *msg)
{
	printf("Error in %s : %s\n", function, msg);
	return (EXIT_FAILURE);
}

/*
philo printf
check if no one is dead or if philo still need to eat before printing in term.
if one is dead or philo finished to eat, pthread exit.
*/
int	pprintf(t_philosopher *philo, char *msg, char *color)
{
	t_data	*data;
	int		is_dead;
	long	time_sstart;

	data = starton();
	pthread_mutex_lock(&data->m_isdead);
	is_dead = data->is_dead;
	if (is_dead == 1)
	{
		pthread_mutex_unlock(&data->m_isdead);
		drop_fork(philo);
		pthread_exit(NULL);
	}
	pthread_mutex_lock(&data->m_start);
	time_sstart = time_stamp_ms() - data->start_ts;
	printf("%ld %d %s%s\033[0m\n", (time_sstart), philo->index, color, msg);
	pthread_mutex_unlock(&data->m_start);
	pthread_mutex_unlock(&data->m_isdead);
	return (0);
}
