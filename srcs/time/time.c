/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:38:36 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/10 18:07:12 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

unsigned long	get_time_diff(struct timeval first, struct timeval second)
{
	unsigned long	start;
	unsigned long	end;

	start = first.tv_sec * 1000 + first.tv_usec / 1000;
	end = second.tv_sec * 1000 + second.tv_usec / 1000;
	return (ft_abs(start - end));
}

unsigned long	get_time(struct timeval *time)
{
	struct timeval	tmp;

	if (time == NULL)
	{
		gettimeofday(&tmp, NULL);
		return ((tmp.tv_sec * 1000) + (tmp.tv_usec / 1000));
	}
	else
		return ((time->tv_sec * 1000) + (time->tv_usec / 1000));
}

void	ft_usleep(long millis)
{
	struct timeval	time;
	struct timeval	finish;

	gettimeofday(&time, NULL);
	while (get_time(NULL) != get_time(&time) + millis)
		usleep(50);
	gettimeofday(&finish, NULL);
	return ;
}

void	ft_msleep(long millis)
{
	struct timeval	time;
	struct timeval	time_a;

	gettimeofday(&time, NULL);
	gettimeofday(&time_a, NULL);
	while (get_time_diff(time, time_a) < (unsigned long)millis)
	{
		gettimeofday(&time_a, NULL);
		usleep(50);
	}
}
