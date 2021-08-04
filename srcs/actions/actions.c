/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:09:48 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/04 20:10:24 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	philo_think(t_philosopher *philosopher)
{
	if (philosopher->index % 2 != 0)
	{
		grab_fork(philosopher, 0);
		grab_fork(philosopher, 1);
	}
	else
	{
		grab_fork(philosopher, 1);
		grab_fork(philosopher, 0);
	}
	if (philosopher->forks == 2)
		philosopher->state = EATING;
}

void	philo_eat(t_philosopher *philosopher)
{
	gettimeofday(&philosopher->time, NULL);
	philosopher->last_eat = philosopher->time;
	print_message(philosopher, "is eating 🍜");
	/*while (get_time_diff(philosopher->time, philosopher->last_eat)
			< (philosopher->data->time_to_eat * 1000))
	{
		gettimeofday(&philosopher->time, NULL);
		usleep(5);
	}*/
	usleep(philosopher->data->time_to_eat * 1000);
	philosopher->eaten++;
	release_fork(philosopher, 0);
	release_fork(philosopher, 1);
	philosopher->state = SLEEPING;
}

void	philo_sleep(t_philosopher *philosopher)
{
	gettimeofday(&philosopher->last_sleep, NULL);
	print_message(philosopher, "is sleeping 🛌");
	/*while (get_time_diff(philosopher->time, philosopher->last_sleep)
			< (philosopher->data->time_to_sleep * 1000))
	{
		gettimeofday(&philosopher->time, NULL);
		usleep(5);
	}*/
	usleep(philosopher->data->time_to_sleep * 1000);
	philosopher->state = THINKING;
	print_message(philosopher, "is thinking 🎓");
}
