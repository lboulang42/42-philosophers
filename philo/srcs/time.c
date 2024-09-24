/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:08:20 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/12 19:13:04 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	time_stamp_ms(void)
{
	struct timeval	tval;
	struct timezone	tzone;
	long			timestamp;
	int				res;

	res = gettimeofday(&tval, &tzone);
	if (res == -1)
		return (err("time_stamp_ms", "gettimeofday"), -1);
	timestamp = (tval.tv_sec * 1000) + (tval.tv_usec / 1000);
	return (timestamp);
}

/*
sleeping for time_to_sleep (ms) by 10us batch while checking is no philo is dead
*/
void	usleep_boost(t_philosopher *philo, long time_to_sleep)
{
	long	start;
	long	current;

	start = time_stamp_ms();
	current = time_stamp_ms();
	while (current < (start + time_to_sleep))
	{
		usleep(10);
		current = time_stamp_ms();
		if (one_is_dead())
		{
			drop_fork(philo);
			pthread_exit(NULL);
		}
	}
}

long	get_time_start(t_data *data)
{
	long	time_start;

	pthread_mutex_lock(&data->m_start);
	time_start = data->start_ts;
	pthread_mutex_unlock(&data->m_start);
	return (time_start);
}
