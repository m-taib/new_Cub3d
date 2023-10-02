/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:58:52 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/02 18:10:11 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <math.h>
#include <stdio.h>

int		is_valid_charset(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != ' '
			&& !ft_strchr("NSEWCO", str[i]))
			return (1);
	}
	return (0);
}

float	set_angle(char 	dir)
{
	float 	an;

	if (dir == 'N')
		an =  (3 * M_PI) / 2;
	else if (dir == 'E')
		an = 0;
	else if (dir == 'S')
		an = M_PI / 2;
	else
		an = M_PI;
	return (an);
}
int		check_chars(char **map)
{
	int		i;
	int		j;
	char	c;

	c = '\0';
	i = -1;
	while (map[++i])
	{
		j = -1;
		if (is_valid_charset(map[i]))
			return (print_error(16));
		while (map[i][++j])
		{
			if (ft_strchr("NSEW", map[i][j]))
			{
				if (get_type()->x)
					return (print_error(13));
				get_type()->pa = set_angle(map[i][j]);
				get_type()->x = j * BLOCSIZE;
				get_type()->y = i * BLOCSIZE;
				c = map[i][j];
				map[i][j] = '0';
			}
		}
	}
	if (!c)
		return (print_error(7));
	return (c);
}
