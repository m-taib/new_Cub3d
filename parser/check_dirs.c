/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:15:14 by mtaib             #+#    #+#             */
/*   Updated: 2023/09/24 20:47:13 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

int	check_path(char *path)
{
	mlx_texture_t	*ptr;

	ptr = mlx_load_png(path);
	if (!ptr)
		return (print_error(4));
	free(ptr);
	return (0);
}

int	count_point(char *str)
{
	int		i;
	int		count;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
			count++;
	}
	return (count);
}

int		save_colors_value(char dir, char *str)
{
	int	i;
	int	j;
	int		n[3];

	j = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == ',')
			return (print_error(2));
		n[j] = ft_atoi(&str[i]);
		if (dir == 'C')
			get_type()->c_color[j] = n[j];
		else
			get_type()->f_color[j] = n[j];
		if (n[j] < 0 || n[j] > 255)
			return (print_error(2));
		while (str[i] && str[i] != ',')
			i++;
		if (str[i] == ',' && !str[i + 1])
			return (print_error(2));
		if (str[i])
			i++;
		if (j < 3)
			j++;
	}
	return (0);
}

int		check_dirs(char dir, char *str)
{
	int		i;

	i = -1;
	if (count_point(str) != 2)
		return (print_error(2));
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9')
			&& str[i] != ','  && str[0] != '-'
			&& str[i] != '+')
			return (print_error(2));
	(void)dir;
	return (1);
}

void		print_map_error(int i)
{
	if (i == 5)
		printf("\tmap must be surounded by walls\n");
	else if (i == 6)
		printf("\tInvalid borders\n");
	else if (i == 7)
		printf("\tInvalid player value\n");
	else if (i == 9)
		printf("\tMap not found\n");
	else if (i == 12)
			printf("\tInvalid map position\n");
	else if (i == 13)
			printf("\tDuplicated player value\n");
	else if (i == 14)
			printf("\tNew line musnt be in map\n");
	else if (i == 16)
			printf("\tInvald map\n");
	else if (i == 17)
			printf("\tEmpty file\n");
}

int		print_error(int	i)
{
	printf("Error :\n");
	if (i == 0)
		printf("\tInvalid direction\n");
	else if (i == 1)
		printf("\tDoes not has a color value\n");
	else if (i == 2)
		printf("\tInvalid color value\n");
	else if (i == 3)
		printf("\tDuplication error\n");
	else if (i == 4)
		printf("\tInvalid path\n");
	else if (i == 10)
		printf("\tInvalid file name\n)");
	else if (i == 11)
		printf("\tBad file descriptor\n");
	print_map_error(i);
	return (1);
}


