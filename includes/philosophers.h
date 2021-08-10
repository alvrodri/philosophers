/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:05:27 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/10 18:29:11 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

struct	s_data;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING
}			t_state;

typedef struct s_philosopher
{
	pthread_t		pid;
	int				index;
	int				eaten;
	int				alive;
	struct timeval	time;
	struct timeval	last_eat;
	struct timeval	last_sleep;
	t_state			state;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_data	*data;
}				t_philosopher;

typedef struct s_data
{
	int						n;
	int						must_eat;
	struct timeval			start_time;
	unsigned long			time_to_die;
	unsigned long			time_to_eat;
	unsigned long			time_to_sleep;
	int						end;
	int						all_alive;
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			*forks;
	t_philosopher			**philosophers;
}				t_data;

int				main(int argc, char **argv);

t_philosopher	*philo_create(t_data *data, int i);
void			*philo_start(void *args);
void			philos_init(t_data *data);
int				philo_eaten(t_data *data);

void			philo_think(t_philosopher *pphilosopher);
void			philo_eat(t_philosopher *philosopher);
void			philo_sleep(t_philosopher *philosopher);

int				forks_init(t_data *data);
pthread_mutex_t	*fork_get(t_philosopher *philosopher, int dir);
void			fork_grab(t_philosopher *philosopher, int dir);
void			fork_release(t_philosopher *philosopher, int dir);

void			print_message(t_philosopher *philosopher,
					t_data *data, char *str);

void			ft_usleep(long millis);
void			ft_msleep(long millis);
unsigned long	get_time(struct timeval *time);
unsigned long	get_time_diff(struct timeval first, struct timeval second);

int				ft_error(int error);
unsigned long	ft_abs(long n);
unsigned long	ft_atoul(char *str);

#endif
