/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:06:31 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/13 14:45:45 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ping_die(t_data *data, long ts, int i)
{
	pthread_mutex_lock(&data->m_isdead);
	printf("%ld %d \033[0;31mdied\e[m\n", \
		(time_stamp_ms() - ts), data->tab_philo[i].index);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->m_isdead);
}

void	check_dead_phil(t_data *data)
{
	long	timestamp_start;
	long	timestamp_last_eat;
	int		i;

	timestamp_start = get_time_start(data);
	while (1)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			if (everyone_ate())
				return ;
			pthread_mutex_lock(&data->m_leat[i]);
			timestamp_last_eat = data->tab_philo[i].time_last_eat_ms;
			if (timestamp_last_eat == -1)
				timestamp_last_eat = timestamp_start;
			pthread_mutex_unlock(&data->m_leat[i]);
			if (time_stamp_ms() >= data->time_die_ms + timestamp_last_eat)
				return (ping_die(data, timestamp_start, i));
		}
		usleep(500);
	}
}

/*return 0 si aucun philo n'est mort*/
int	one_is_dead(void)
{
	t_data	*data;
	int		tmp;

	data = starton();
	pthread_mutex_lock(&data->m_isdead);
	tmp = data->is_dead;
	pthread_mutex_unlock(&data->m_isdead);
	if (tmp != 0)
		return (1);
	return (0);
}

/*
Handle only one philo => one_phil();
Separate pairs and impairs philos (little delay);
While no one dead and not finished eating : 
 ft_pickfork(), ft_eat(), ft_sleepthink(), think
*/

int	everyone_ate(void)
{
	t_data	*data;
	int		i;
	int		need_to_eat;

	data = starton();
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_lock(&data->m_leat[i]);
		need_to_eat = data->tab_philo[i].need_to_eat;
		pthread_mutex_unlock(&data->m_leat[i]);
		if (need_to_eat > 0)
			return (0);
	}
	return (1);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (philo->n_philo == 1)
		one_phil(philo);
	if (philo->index % 2)
		usleep(philo->time_to_eat_ms * 500);
	while (!one_is_dead())
	{
		if (everyone_ate())
			break ;
		if (philo->n_philo % 2 == 1)
			usleep_boost(philo, philo->time_to_die_ms / 10);
		ft_pickfork(philo);
		ft_eat(philo);
		ft_sleepthink(philo);
	}
	drop_fork(philo);
	pthread_exit(NULL);
}
