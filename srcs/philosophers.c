/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvrodri <alvrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 18:04:42 by alvrodri          #+#    #+#             */
/*   Updated: 2021/08/04 20:20:49 by alvrodri         ###   ########.fr       */
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
	struct timeval time;

	data->n = ft_atoul(argv[0]);
	data->time_to_die = ft_atoul(argv[1]);
	data->time_to_eat = ft_atoul(argv[2]);
	data->time_to_sleep = ft_atoul(argv[3]);
	if (argc == 5)
		data->must_eat = ft_atoul(argv[4]);
	else
		data->must_eat = -1;
	gettimeofday(&time, NULL);
	data->start_time = time;
	data->end = 0;
}

void	*start_philosopher(void *args)
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
	}
	release_fork(philosopher, 0);
	release_fork(philosopher, 1);
	return (NULL);
}

void	start_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = (t_philosopher **)malloc(sizeof(t_philosopher *) * data->n);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * data->n);
	if (!data->philosophers || !data->forks)
		exit(ft_error(printf("Could not allocate enough memory.\n")));
	while (i < data->n)
	{
		data->philosophers[i] = (t_philosopher *)malloc(sizeof(t_philosopher));
		if (!data->philosophers[i])
			exit(ft_error(printf("Could not allocate enough memory.\n")));
		pthread_mutex_init(&data->forks[i], NULL);
		gettimeofday(&data->philosophers[i]->time, NULL);
		data->philosophers[i]->index = i + 1;
		data->philosophers[i]->state = THINKING;
		data->philosophers[i]->data = data;
		data->philosophers[i]->eaten = 0;
		data->philosophers[i]->alive = 1;
		data->philosophers[i]->forks = 0;
		data->philosophers[i]->last_eat = data->philosophers[i]->time;
		pthread_create(&data->philosophers[i]->pid, NULL, start_philosopher, data->philosophers[i]);
		i++;
	}
}

void	check_death(t_data *data)
{
	struct timeval time;
	int	i;

	while (!data->end)
	{
		i = 0;
		while (i < data->n)
		{
			gettimeofday(&time, NULL);
			if (get_time_diff(time, data->philosophers[i]->last_eat) >= data->time_to_die * 1000)
			{
				print_message(data->philosophers[i], "died 💀");
				data->philosophers[i]->alive = 0;
				data->philosophers[i]->data->end = 1;
				break ;
			}
			i++;
		}
	}
	join_threads(data);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_data	data;

	if (argc > 6 || argc < 5)
		return (ft_error(printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [num_eat]\n", argv[0])));
	set_data(++argv, --argc, &data);
	pthread_mutex_init(&data.print_mutex, NULL);
	start_philosophers(&data);
	check_death(&data);
	return (0);
}
