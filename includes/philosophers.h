/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:05:27 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/04 20:16:48 by alvrodri         ###   ########.fr       */
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

typedef struct	s_philosopher
{
	pthread_t		pid;
	int				index;
	int				forks;
	int				eaten;
	int				alive;
	struct timeval	time;
	struct timeval	last_eat;
	struct timeval	last_sleep;
	t_state			state;
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
	pthread_mutex_t			print_mutex;
	pthread_mutex_t			*forks;
	t_philosopher			**philosophers;
}				t_data;

int	main(int argc, char **argv);

void	philo_think(t_philosopher *pphilosopher);
void	philo_eat(t_philosopher *philosopher);
void	philo_sleep(t_philosopher *philosopher);

pthread_mutex_t	*get_fork(t_philosopher *philosopher, int dir);
void	grab_fork(t_philosopher *philosopher, int dir);
void	release_fork(t_philosopher *philosopher, int dir);

void	print_message(t_philosopher *philosopher, char *str);

void	ft_usleep(long millis);
unsigned long	get_time(struct timeval *time);
unsigned long	get_time_diff(struct timeval first, struct timeval second);

int	ft_error(int error);
unsigned long	ft_abs(long n);
unsigned long	ft_atoul(char *str);

#endif
