/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:09:48 by alvrodri          #+#    #+#             */
/*   Updated: 2021/09/09 11:49:37 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	philo_think(t_philosopher *philosopher)
{
	if (philosopher->even)
	{
		fork_grab(philosopher, 0);
		fork_grab(philosopher, 1);
	}
	else
	{
		if (philosopher->left_fork == philosopher->right_fork)
		{
			fork_grab(philosopher, 0);
			philosopher->left_fork = NULL;
			philosopher->right_fork = NULL;
		}
		else
		{
			fork_grab(philosopher, 1);
			fork_grab(philosopher, 0);
		}
	}
	if (philosopher->left_fork != philosopher->right_fork)
		philosopher->state = EATING;
}

void	philo_eat(t_philosopher *philosopher)
{	
	gettimeofday(&philosopher->time, NULL);
	philosopher->last_eat = philosopher->time;
	print_message(philosopher, NULL, "is eating 🍜");
	ft_msleep(philosopher->data->time_to_eat);
	fork_release(philosopher, 0);
	fork_release(philosopher, 1);
	philosopher->eaten++;
	philosopher->state = SLEEPING;
}

void	philo_sleep(t_philosopher *philosopher)
{
	gettimeofday(&philosopher->last_sleep, NULL);
	print_message(philosopher, NULL, "is sleeping 🛌");
	ft_msleep(philosopher->data->time_to_sleep);
	philosopher->state = THINKING;
	print_message(philosopher, NULL, "is thinking 🎓");
}
