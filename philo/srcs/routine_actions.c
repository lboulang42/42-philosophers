/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:40:16 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/12 19:51:06 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_pickfork(t_philosopher *philo)
{
	if (philo->index % 2 == 1)
	{
		pthread_mutex_lock(philo->fork_droite);
		philo->lock_droite = 1;
		pprintf(philo, "has taken a fork", "\033[0;33m");
		pthread_mutex_lock(philo->fork_gauche);
		philo->lock_gauche = 1;
		pprintf(philo, "has taken a fork", "\033[0;33m");
	}
	else
	{
		pthread_mutex_lock(philo->fork_gauche);
		philo->lock_gauche = 1;
		pprintf(philo, "has taken a fork", "\033[0;33m");
		pthread_mutex_lock(philo->fork_droite);
		philo->lock_droite = 1;
		pprintf(philo, "has taken a fork", "\033[0;33m");
	}
}

void	ft_eat(t_philosopher *philo)
{
	t_data	*data;

	data = starton();
	pprintf(philo, "is eating", "\033[0;32m");
	pthread_mutex_lock(&data->m_leat[philo->index]);
	philo->time_last_eat_ms = time_stamp_ms();
	pthread_mutex_unlock(&data->m_leat[philo->index]);
	usleep_boost(philo, philo->time_to_eat_ms);
	pthread_mutex_lock(&data->m_leat[philo->index]);
	philo->need_to_eat--;
	pthread_mutex_unlock(&data->m_leat[philo->index]);
	drop_fork(philo);
}

void	ft_sleepthink(t_philosopher *philo)
{
	pprintf(philo, "is sleeping", "\033[0;36m");
	usleep_boost(philo, philo->time_to_sleep_ms);
	pprintf(philo, "is thinking", "\033[0;34m");
}

void	one_phil(t_philosopher *philo)
{
	pprintf(philo, "has taken a fork", "\033[0;33m");
	usleep(philo->time_to_die_ms * 1000);
	pprintf(philo, "died", "\033[0;31m");
	pthread_exit(NULL);
}

void	drop_fork(t_philosopher *philo)
{
	if (philo->lock_droite)
		pthread_mutex_unlock(philo->fork_droite);
	if (philo->lock_gauche)
		pthread_mutex_unlock(philo->fork_gauche);
	philo->lock_droite = 0;
	philo->lock_gauche = 0;
}
