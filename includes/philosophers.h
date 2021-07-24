/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:05:27 by alvrodri          #+#    #+#             */
/*   Updated: 2021/07/23 19:13:58 by alvrodri         ###   ########.fr       */
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

typedef struct	s_fork
{
	int				in_use;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct	s_philosopher
{
	pthread_t		pid;
	int				index;
	int				forks;
	int				eaten;
	int				alive;
	struct timeval	last_eat;
	t_state			state;
	struct s_data	*data;
}				t_philosopher;

typedef struct s_data
{
	int				n;
	int				must_eat;
	struct timeval	start_time;
	unsigned long			time_to_die;
	unsigned long			time_to_eat;
	unsigned long			time_to_sleep;
	pthread_t				death_pid;
	t_fork			**forks;
	t_philosopher	**philosophers;
}				t_data;

int	main(int argc, char **argv);

#endif
