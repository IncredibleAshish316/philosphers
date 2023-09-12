/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkargs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:54:01 by cvidon            #+#    #+#             */
/*   Updated: 2022/08/08 16:54:02 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * The function checks if a given string consists only of numeric characters.
 * 
 * @param str The parameter `str` is a pointer to a character array (string) that we want to check if
 * it contains only numeric characters.
 * 
 * @return either TRUE or FALSE.
 */

static int	ft_is_numeric(char const *str)
{
	int	i;

	i = 0;
	if (*str == '+')
		str++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] == '\0')
		return (TRUE);
	return (FALSE);
}

/**
 * The function checks if the number of arguments is within a valid range, if the arguments are numeric
 * and within a valid range, and returns a 0 or 1 status.
 * 
 * @param ac The parameter `ac` represents the number of arguments passed to the program.
 * @param av The parameter `av` is an array of strings, where each string represents a command-line
 * argument passed to the program.
 * 
 * @return either 0 or 1.
 */

int	ft_check_args(int ac, char const *const *av)
{
	if (ac < 5)
	{
		write (2, "Error: Too few arguments.\n", 26);
		return (1);
	}
	if (ac > 6)
	{
		write (2, "Error: Too many arguments.\n", 27);
		return (1);
	}
	while (ac-- > 1)
	{
		if (ft_is_numeric (av[ac]) == FALSE)
		{
			write (2, "Error: Invalid character.\n", 26);
			return (1);
		}
		if (ft_atol (av[ac]) > INT_MAX || ft_atol (av[ac]) < 0)
		{
			write (2, "Error: Out of range value.\n", 27);
			return (1);
		}
	}
	return (0);
}
