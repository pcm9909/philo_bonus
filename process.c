#include "philosopher.h"

static void	ft_take_forks(t_philo *philo)
{
	sem_wait(philo->resource->forks);
	print_status(philo, FORK);
	sem_wait(philo->resource->forks);
	print_status(philo, FORK);
}

static void	ft_drop_forks(t_philo *philo)
{
	sem_post(philo->resource->forks);
	sem_post(philo->resource->forks);
}

static void	ft_eat(t_philo *philo)
{
	print_status(philo, EAT);
	usleep(philo->resource->time_eat * 1000);
	sem_wait(philo->resource->eat);
	philo->cnt_eat++;
	philo->time_last_eat = get_time();
	sem_post(philo->resource->eat);
}

static void	ft_sleep(t_philo *philo)
{
	print_status(philo, SLEEP);
	usleep(philo->resource->time_sleep * 1000);
}

int check_finish(t_philo *philo, int status)
{
	sem_wait(philo->resource->cmp_finish);
	if (status == 2)
	{
		sem_post(philo->resource->cmp_finish);
		kill(philo->pid, SIGINT);
	}
	if (philo->resource->num_philos % 2 == 1)
	{
		if (status == 1 && philo->id == philo->resource->num_philos - 1)
		{
			sem_post(philo->resource->cmp_finish);
			kill(0, SIGINT);
		}
		sem_post(philo->resource->cmp_finish);
	}
	else
	{
		if (status == 1 && philo->id == philo->resource->num_philos)
		{
			sem_post(philo->resource->cmp_finish);
			kill(0, SIGINT);
		}
		sem_post(philo->resource->cmp_finish);
	}
	return (0);
}


static int check_dead(t_philo *philo)
{
	sem_wait(philo->resource->eat);
	if (get_time() - philo->time_last_eat >= philo->resource->time_die)
	{
		print_status(philo, DIE);
		check_finish(philo, 2);
		sem_post(philo->resource->eat);
		return (1);
	}
	else if (philo->resource->cnt_must_eat != -1 && philo->cnt_eat >= philo->resource->cnt_must_eat)
	{
		check_finish(philo, 1);
		sem_post(philo->resource->eat);
	}
	sem_post(philo->resource->eat);
	return (0);
}

void *checker(void *philos)
{
	t_philo *philo;
	philo = (t_philo *)philos;
	int i;
	int status;

	status = 1;
	while (status)
	{
		if (check_dead(philo))
		{
				status = 0;
		}
	}
	pthread_join(philo->checker, NULL);
}

void routine(t_philo *philo)
{
	pthread_create(&philo->checker, NULL, checker, philo);
	print_status(philo, THINK);
	if (philo->id % 2 == 0)
	{
		usleep(philo->resource->time_eat * 1000);
	}
	while (1)
	{
		//check_finish(philo, 0);
		ft_take_forks(philo);
		ft_eat(philo);
		ft_drop_forks(philo);
		ft_sleep(philo);
		print_status(philo, THINK);
	}
}

void fork_philos(t_resource *resource)
{
	int i;

	i = 0;
	while(i < resource->num_philos)
	{
		resource->philos[i].pid = fork();
		if(resource->philos[i].pid == 0)
		{
			routine(&resource->philos[i]);
		}
		else if (resource->philos[i].pid < 0)
		{
			print_error(FORK_ERR);
		}
		usleep(100);
		i++;
	}
}