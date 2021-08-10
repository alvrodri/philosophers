/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:26:45 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/10 18:31:01 by alvrodri         ###   ########.fr       */
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

	fork = fork_get(philosopher, dir);
	if (fork == NULL)
		return ;
	if (dir == 0 && fork_get(philosopher, 1) == fork_get(philosopher, 0))
		return ;
	pthread_mutex_lock(fork);
	if (dir == 0)
		philosopher->left_fork = fork;
	else if (dir == 1)
		philosopher->right_fork = fork;
	print_message(philosopher, NULL, "has taken a fork");
}

void	fork_release(t_philosopher *philosopher, int dir)
{
	pthread_mutex_t	*fork;

	fork = fork_get(philosopher, dir);
	if (fork == NULL)
		return ;
	if (dir == 0)
		philosopher->left_fork = NULL;
	else if (dir == 1)
		philosopher->right_fork = NULL;
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
