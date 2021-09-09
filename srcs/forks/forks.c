/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:26:45 by alvrodri          #+#    #+#             */
/*   Updated: 2021/09/08 13:04:54 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

pthread_mutex_t	*fork_get(t_philosopher *philosopher, int dir)
{
	if (dir == 0)
	{
		if (philosopher->index == 0)
			return (&philosopher->data->forks[philosopher->data->n - 1]);
		else
			return (&philosopher->data->forks[philosopher->index - 1]);
	}
	else if (dir == 1)
		return (&philosopher->data->forks[philosopher->index]);
	return (NULL);
}

void	fork_grab(t_philosopher *philosopher, int dir)
{
	pthread_mutex_t	*fork;

	if (dir == 0)
		fork = philosopher->left_fork;
	else
		fork = philosopher->right_fork;
	if (fork == NULL)
		return ;
	pthread_mutex_lock(fork);
	print_message(philosopher, NULL, "has taken a fork");
}

void	fork_release(t_philosopher *philosopher, int dir)
{
	pthread_mutex_t	*fork;

	if (dir == 0)
		fork = philosopher->left_fork;
	else
		fork = philosopher->right_fork;
	if (fork != NULL)
		pthread_mutex_unlock(fork);
}

int	forks_init(t_data *data)
{
	int	i;

	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->n)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (0);
		i++;
	}
	return (1);
}
