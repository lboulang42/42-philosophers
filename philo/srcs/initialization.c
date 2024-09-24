/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:46:30 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/13 14:45:56 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
malloc tabs for forks and last eat
init mutex for forks, lasteat, start andisdead 
on error :
	- tabs are free and mutex destroyed accordingly. 
	- return EXIT_FAILURE (from err() function).
*/
static int	init_mutex(t_data *data)
{
	int	i;

	data->m_fork = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->m_fork)
		return (err(I_MTX, "malloc"));
	data->m_leat = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	if (!data->m_leat)
		return (free(data->m_fork), err(I_MTX, "malloc"));
	i = -1;
	while (++i < data->n_philo)
		if (pthread_mutex_init(&data->m_fork[i], NULL) != EXIT_SUCCESS)
			return (d_fork(data, i), free(data->m_leat), err(I_MTX, "m_fork"));
	i = -1;
	while (++i < data->n_philo)
		if (pthread_mutex_init(&data->m_leat[i], NULL) != EXIT_SUCCESS)
			return (d_fork(data, i), d_lasteat(data, i), err(I_MTX, "m_leat"));
	if (pthread_mutex_init(&data->m_start, NULL) != EXIT_SUCCESS)
		return (d_mutex(data, 0), err(I_MTX, "m_start"));
	if (pthread_mutex_init(&data->m_isdead, NULL) != EXIT_SUCCESS)
		return (d_mutex(data, 1), err(I_MTX, "m_dead"));
	return (EXIT_SUCCESS);
}

/*
malloc le tab de philos et set tous les philos avec les arguments nécessaire
a la routine
*/
static int	init_philo(t_data *data)
{
	int	i;

	i = -1;
	data->tab_philo = malloc(sizeof(t_philosopher) * data->n_philo);
	if (!data->tab_philo)
		return (err(I_PHIL, ERR_MALL));
	while (++i < data->n_philo)
	{
		data->tab_philo[i].n_philo = data->n_philo;
		data->tab_philo[i].index = i;
		data->tab_philo[i].time_to_die_ms = data->time_die_ms;
		data->tab_philo[i].time_to_eat_ms = data->time_eat_ms;
		data->tab_philo[i].time_to_sleep_ms = data->time_sleep_ms;
		data->tab_philo[i].need_to_eat = data->must_eat;
		data->tab_philo[i].lock_droite = 0;
		data->tab_philo[i].lock_gauche = 0;
		data->tab_philo[i].fork_gauche = &data->m_fork[i];
		if (i + 1 < data->n_philo)
			data->tab_philo[i].fork_droite = &data->m_fork[i + 1];
		else
			data->tab_philo[i].fork_droite = &data->m_fork[0];
		data->tab_philo[i].time_last_eat_ms = -1;
	}
	return (EXIT_SUCCESS);
}

/*
start every threads, on error detach created threads. return exit_failure
*/
static int	start_threads(t_data *data)
{
	int	i;

	i = -1;
	data->start_ts = time_stamp_ms();
	if (data->start_ts == -1)
		return (err("time_stamp_ms", "can't get starting time"));
	while (++i < data->n_philo)
		if (pthread_create(&data->tab_philo[i].thread, NULL, &routine, \
			(void *)&data->tab_philo[i]) != EXIT_SUCCESS)
			return (detach(data, i), err(I_THRD, "pcreate"));
	check_dead_phil(data);
	return (EXIT_SUCCESS);
}

int	init_all(t_data *data)
{
	int	i;

	if (init_mutex(data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_philo(data) == EXIT_FAILURE)
		return (d_mutex(data, 2), EXIT_FAILURE);
	if (start_threads(data) == EXIT_FAILURE)
		return (d_mutex(data, 2), free(data->tab_philo), EXIT_FAILURE);
	i = -1;
	while (++i < data->n_philo)
		pthread_join(data->tab_philo[i].thread, NULL);
	return (free(data->tab_philo), d_mutex(data, 2), EXIT_SUCCESS);
}
