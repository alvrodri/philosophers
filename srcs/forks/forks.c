/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:26:45 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/04 20:23:44 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

pthread_mutex_t	*get_fork(t_philosopher *philosopher, int dir)
{
	if (dir == 0)
		return (&philosopher->data->forks[philosopher->index - 1]);
	else if (dir == 1)
	{
		if (philosopher->index == philosopher->data->n)
			return (&philosopher->data->forks[0]);
		else
			return (&philosopher->data->forks[philosopher->index]);
	}
	return (NULL);
}

void	grab_fork(t_philosopher *philosopher, int dir)
{
	pthread_mutex_t	*fork;

	fork = get_fork(philosopher, dir);
	if (fork == NULL)
		return ;
	pthread_mutex_lock(fork);
	philosopher->forks++;
	print_message(philosopher, "has taken a fork");
}

void	release_fork(t_philosopher *philosopher, int dir)
{
	pthread_mutex_t	*fork;

	fork = get_fork(philosopher, dir);
	if (fork == NULL)
		return ;
	philosopher->forks--;
	pthread_mutex_unlock(fork);
}
