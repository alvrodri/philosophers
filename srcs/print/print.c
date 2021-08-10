/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 16:31:06 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/10 12:42:34 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosophers.h"

void	print_message(t_philosopher *philosopher, t_data *data, char *str)
{
	struct timeval	time;

	if (data)
		pthread_mutex_lock(&data->print_mutex);
	else
		pthread_mutex_lock(&philosopher->data->print_mutex);
	gettimeofday(&time, NULL);
	if (philosopher != NULL && !philosopher->data->end)
		printf("\e[0;32m%-5lu\e[0m | \e[0;33m%d\e[0m %s\n",
			get_time_diff(philosopher->data->start_time, time)
				, philosopher->index + 1, str);
	else
	{
		if (philosopher == NULL && !data->end)
			printf("\e[0;36m%s\e[0m\n", str);
	}
	if (data)
		pthread_mutex_unlock(&data->print_mutex);
	else
		pthread_mutex_unlock(&philosopher->data->print_mutex);
}
