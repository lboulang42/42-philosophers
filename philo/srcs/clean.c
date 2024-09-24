/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 18:02:32 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/12 19:25:49 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*destroy tous les mutex "fork" jusqu'a limit (si pas de limit, destroy tous).*/
void	d_fork(t_data *data, int limit)
{
	int	i;

	i = -1;
	if (limit == -1)
		limit = data->n_philo;
	while (++i < limit)
		pthread_mutex_destroy(&data->m_fork[i]);
	free(data->m_fork);
}

/*destroy tous les mutex "leat" jusqu'a limit (si pas de limit, destroy tous).*/
void	d_lasteat(t_data *data, int limit)
{
	int	i;

	i = -1;
	if (limit == -1)
		limit = data->n_philo;
	while (++i < limit)
		pthread_mutex_destroy(&data->m_leat[i]);
	free(data->m_leat);
}

/*
destroy every forks and every lasteat mutex 
flag : 1 : destroy startmutex 
flag : 2 : destroy startmutex && m_isdead
flag : 0 : don't destroy start or isdead mutexs
*/
void	d_mutex(t_data *data, int flag)
{
	d_fork(data, -1);
	d_lasteat(data, -1);
	if (flag == 2)
		pthread_mutex_destroy(&data->m_isdead);
	if (flag >= 1)
		pthread_mutex_destroy(&data->m_start);
}

/*detach every thread before limit*/
void	detach(t_data *data, int limit)
{
	int	i;

	i = -1;
	if (limit == -1)
		limit = data->n_philo;
	while (++i < limit)
		pthread_detach(data->tab_philo[i].thread);
}
