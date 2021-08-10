/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:04:42 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/10 18:30:44 by alvrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n)
	{
		pthread_join(data->philosophers[i]->pid, NULL);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	i = 0;
	while (i < data->n)
	{
		pthread_mutex_destroy(&(data->forks[i]));
		i++;
	}
}

void	set_data(char **argv, int argc, t_data *data)
{
	struct timeval	time;

	data->n = ft_atoul(argv[0]);
	data->time_to_die = ft_atoul(argv[1]);
	data->time_to_eat = ft_atoul(argv[2]);
	data->time_to_sleep = ft_atoul(argv[3]);
	if (argc == 5)
		data->must_eat = ft_atoul(argv[4]);
	else
		data->must_eat = -1;
	data->all_alive = 1;
	gettimeofday(&time, NULL);
	data->start_time = time;
	data->end = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	if (!forks_init(data))
		exit(ft_error(printf("%s: Could not initialize forks.\n", argv[-1])));
}

void	check_death(t_data *data)
{
	struct timeval	time;
	int				i;

	while (!data->end)
	{
		i = 0;
		while (i < data->n)
		{
			gettimeofday(&time, NULL);
			if (get_time_diff(time, data->philosophers[i]->last_eat)
				>= (data->time_to_die + 5))
			{
				print_message(data->philosophers[i], NULL, "died 💀");
				data->philosophers[i]->alive = 0;
				data->all_alive = 0;
				data->end = 1;
				break ;
			}
			i++;
		}
		if (philo_eaten(data))
		{
			if (data->all_alive)
				print_message(NULL, data,
					"💥  All the philosophers have eaten! 💥");
			break ;
		}
		ft_msleep(1);
	}
	data->end = 1;
	join_threads(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc > 6 || argc < 5)
		return (ft_error(printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> \
<time_to_sleep> [num_eat]\n", argv[0])));
	set_data(++argv, --argc, &data);
	philos_init(&data);
	check_death(&data);
	return (0);
}
