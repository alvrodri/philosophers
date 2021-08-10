/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:26:45 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/05 13:44:55 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

pthread_mutex_t	*get_fork(t_philosopher *philosopher, int dir)
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

void	grab_fork(t_philosopher *philosopher, int dir)
{
	pthread_mutex_t	*fork;

	fork = get_fork(philosopher, dir);
	if (fork == NULL)
		return ;
	if (dir == 0 && get_fork(philosopher, 1) == get_fork(philosopher, 0))
		return ;
	pthread_mutex_lock(fork);
	if (dir == 0)
		philosopher->left_fork = fork;
	else if (dir == 1)
		philosopher->right_fork = fork;
	print_message(philosopher, NULL, "has taken a fork");
}

void	release_fork(t_philosopher *philosopher, int dir)
{
	pthread_mutex_t	*fork;

	fork = get_fork(philosopher, dir);
	if (fork == NULL)
		return ;
	if (dir == 0)
		philosopher->left_fork = NULL;
	else if (dir == 1)
		philosopher->right_fork = NULL;
	pthread_mutex_unlock(fork);
}

int	init_forks(t_data *data)
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
