/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 11:46:01 by alvrodri          #+#    #+#             */
/*   Updated: 2021/09/07 10:27:45 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

t_philosopher	*philo_create(t_data *data, int i)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (!philo)
	{
		ft_error(printf("Could not allocate enough memory.\n"));
		return (NULL);
	}
	gettimeofday(&philo->time, NULL);
	philo->index = i;
	philo->state = THINKING;
	philo->data = data;
	philo->eaten = 0;
	philo->alive = 1;
	philo->last_eat = philo->time;
	philo->left_fork = &data->forks[philo->index];
	philo->right_fork = &data->forks[philo->index + 1 % data->n];
	philo->odd_even = philo->index % 2;
	pthread_create(&philo->pid, NULL, philo_start, philo);
	return (philo);
}

void	*philo_start(void *args)
{
	t_philosopher	*philosopher;

	philosopher = (t_philosopher *)args;
	while (!philosopher->data->end)
	{
		if (philosopher->state == THINKING)
			philo_think(philosopher);
		else if (philosopher->state == EATING)
			philo_eat(philosopher);
		else if (philosopher->state == SLEEPING)
			philo_sleep(philosopher);
		if (philosopher->eaten == philosopher->data->must_eat)
			break ;
	}
	fork_release(philosopher, 0);
	fork_release(philosopher, 1);
	return (NULL);
}

int	philos_init(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = (t_philosopher **)malloc(sizeof(t_philosopher *)
			* data->n);
	if (!data->philosophers)
		return (ft_error(printf("Could not allocate enough memory.\n")));
	while (i < data->n)
	{
		data->philosophers[i] = philo_create(data, i);
		if (data->philosophers[i] == NULL)
			return (1);
		usleep(50);
		i++;
	}
	return (0);
}

int	philo_eaten(t_data *data)
{
	int	n;

	if (data->must_eat == -1)
		return (0);
	n = 0;
	while (n < data->n)
	{
		if (data->philosophers[n]->eaten < data->must_eat)
			return (0);
		n++;
	}
	return (1);
}
