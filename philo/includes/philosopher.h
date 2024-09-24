/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboulang <lboulang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:21:36 by lboulang          #+#    #+#             */
/*   Updated: 2023/10/12 19:54:04 by lboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef ARGS
#  define ARGS "Number_of_philosophers time_to_die time_to_eat time_to_sleep"
# endif
# ifndef NEAT
#  define NEAT "Number_of_times_each_philosopher_must_eat"
# endif
# ifndef ERR_TOOM
#  define ERR_TOOM "Too many Arguments"
# endif
# ifndef ERR_MALL
#  define ERR_MALL "Malloc Error"
# endif
# ifndef ERR_INVAL
#  define ERR_INVAL "Invalid Argument"
# endif
# ifndef I_MTX
#  define I_MTX "init_mutex()"
# endif
# ifndef I_PHIL
#  define I_PHIL "init_philo()"
# endif
# ifndef I_THRD
#  define I_THRD "init_thread()"
# endif

typedef struct s_philosopher
{
	int				n_philo;
	int				index;
	int				need_to_eat;
	long			time_to_die_ms;
	long			time_to_eat_ms;
	long			time_to_sleep_ms;
	long			time_last_eat_ms;
	int				lock_droite;
	int				lock_gauche;
	pthread_mutex_t	*fork_droite;
	pthread_mutex_t	*fork_gauche;
	pthread_t		thread;

}					t_philosopher;

/*
m_fork=>tab of forks
m_leat=>tab of mutex "last eat"
*/
typedef struct s_data
{
	int				n_philo;
	int				must_eat;
	int				is_dead;
	long			time_die_ms;
	long			time_eat_ms;
	long			time_sleep_ms;
	long			start_ts;
	t_philosopher	*tab_philo;
	pthread_mutex_t	m_isdead;
	pthread_mutex_t	m_start;
	pthread_mutex_t	*m_fork;
	pthread_mutex_t	*m_leat;
}					t_data;

/*main.c*/
int			main(int ac, char **av);
t_data		*starton(void);
/*print.c*/
int			err(char *function, char *msg);
int			pprintf(t_philosopher *philo, char *msg, char *color);
/*parsing.c*/
int			parse_philo(t_data *data, int ac, char **av);
/*initialization.c*/
int			init_all(t_data *data);
/*routine.c*/
void		check_dead_phil(t_data *data);
void		*routine(void *arg);
int			one_is_dead(void);
int			everyone_ate(void);
/*routine_action.c*/
void		one_phil(t_philosopher *philo);
void		ft_sleepthink(t_philosopher *philo);
void		ft_eat(t_philosopher *philo);
void		ft_pickfork(t_philosopher *philo);
void		drop_fork(t_philosopher *philo);
/*clean.c*/
void		detach(t_data *data, int limit);
void		d_mutex(t_data *data, int flag);
void		d_lasteat(t_data *data, int limit);
void		d_fork(t_data *data, int limit);
/*time.c*/
long		time_stamp_ms(void);
void		usleep_boost(t_philosopher *philo, long time_to_sleep);
long		get_time_start(t_data *data);
#endif