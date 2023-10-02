/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:58:52 by mtaib             #+#    #+#             */
/*   Updated: 2023/10/02 22:24:03 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"
#include <stdio.h>

void ft_square(char **map)
{
	int		i;
	int		j;
	int		max;

	max = max_len();
	i = -1;
	while (map[++i])
	{
		j = ft_strlen(map[i]);
		while (j++ < max)
			map[i] = ft_strjoin(map[i], " ");
	}
}

int		check_newline(int fd, char *str)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			str = ft_strjoin(str, line);
		if (line[0] != '\n' && !is_all_value(line, ' '))
			return (print_error(16));
	}
	return (0);	
}

int		handle_map(int	fd)
{
	char	*line;
	char	*str;

	str = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n')
			str = ft_strjoin(str, line);
		if (str && line[0] == '\n')
			if (check_newline(fd, str))
				return (1);
	}
	if (!str)
		return (print_error(9));
	get_type()->map = ft_split(str, '\n');
	ft_square(get_type()->map);
	if (check_map_errors(get_type()->map))
		return (1);
	return (0);
}

int		check_file_content(int 	fd)
{
	char	*line;
	int		cnl;

	cnl = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			if (!cnl)
				print_error(17);
			break ;
		}
		// if (get_type()->dirNbs < 6
		// 		&& ft_strchr("10", line[0])
		// 		&& !ft_strchr(line, ','))
		// 	return (print_error(12));
		if (check_elements(line))
			return (1);
		if (get_type()->dirNbs == 6)
		{
			// if (handle_map(fd))
			// 	return (1);
			return (0);
		}
		cnl++;
	}
	return (0);
}

int		ft_parse(char *str)
{
	int		fd;
	
	if (check_file_name(str))
		return (print_error(10));
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (print_error(11));
	if (check_file_content(fd))
	{
		t_dirs *tmp;
		tmp = get_type()->directions;
		while (tmp)
		{
			printf("%s\n",tmp->key);
			tmp = tmp->next;
		}
		free_list(&get_type()->directions);
		free(get_type());
		return (1);
		// return (free_list(get_type()->directions), 
		// 		free(get_type()), 1);
	}	
	return (0);
}
