/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:39:14 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 18:43:12 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 ** @brief      The philosopher take the forks.
 **
 ** - Using a "locking hierarchy" to prevent deadlock.
 ** - Handle the 'one philo' case by making sure there are not only one fork on
 **   the table: 'lfork == rfork'.
 **
 ** @param[in]  self the philosopher's data.
 ** @return     0 if everything went well, otherwise 1.
 */

static int	ft_start_eating(t_philo *self)
{
	pthread_mutex_lock (&self->fork[ft_min (self->lfork, self->rfork)]);
	ft_print (self, "has taken a fork");
	if (self->lfork == self->rfork)
	{
		pthread_mutex_unlock (&self->fork[ft_min (self->lfork, self->rfork)]);
		return (1);
	}
	pthread_mutex_lock (&self->fork[ft_max (self->lfork, self->rfork)]);
	ft_print (self, "has taken a fork");
	ft_print (self, "is eating");
	return (0);
}

/*
 ** @brief      The philosopher release the forks and sleep.
 **
 ** We print "is sleeping" before forks release and we sleep after forks release
 ** to make sure that "is sleeping" is printed right after "is eating".
 **
 ** @param[in]  self the philosopher's data.
 ** @return     0 if everything went well.
 */

static int	ft_finish_eating(t_philo *self)
{
	ft_print (self, "is sleeping");
	pthread_mutex_unlock (&self->fork[ft_max (self->lfork, self->rfork)]);
	pthread_mutex_unlock (&self->fork[ft_min (self->lfork, self->rfork)]);
	ft_msleep (self->data->time_slp);
	return (0);
}

/*
 ** @brief      Philosopher's meal.
 **
 ** - A meal is considered as +1 meal as soon as it starts.  Even though they
 **   are already considered as 'done' philos that started to eat have to
 **   properly finish eating by passing through 'time_eat'.
 **
 ** @param[in]  self the philosopher's data.
 ** @return     0 if everything went well, otherwise 1.
 */

static int	ft_eating(t_philo *self)
{
	if (ft_start_eating (self) != 0)
		return (1);
	pthread_mutex_lock (&self->data->mutex[MEALS]);
	self->last_meal = ft_abs_time ();
	self->meals_counter++;
	pthread_mutex_unlock (&self->data->mutex[MEALS]);
	if (ft_check_done (self))
	{
		ft_finish_eating (self);
		return (1);
	}
	ft_msleep (self->data->time_eat);
	ft_finish_eating (self);
	return (0);
}



/**
 * The function `ft_simulation` is a thread function that simulates the behavior of a philosopher,
 * where they eat, think, and check if they have died.
 * 
 * @param arg The "arg" parameter is a void pointer that is passed to the function. In this case, it is
 * casted to a "t_philo" pointer, which means it is expected to point to a structure of type "t_philo".
 * The function then uses this pointer to access the data
 * 
 * @return NULL.
 */

void	*ft_simulation(void *arg)
{
	t_philo	*self;

	self = (t_philo *) arg;
	if (self->id % 2 == 0)
	{
		ft_print (self, "is thinking");
		ft_msleep (self->data->time_eat);
	}
	while (1)
	{
		if (ft_check_died(self))
			break ;
		if (ft_eating (self) != 0)
			break ;
		ft_print (self, "is thinking");
		ft_msleep (self->data->time_thk);
	}
	return (NULL);
}
