/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaib <mtaib@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 10:20:15 by mbaanni           #+#    #+#             */
/*   Updated: 2023/10/02 22:25:30 by mtaib            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cub3D.h"

void	load_mlx(t_mlx *mlx)
{
	mlx->mlx = mlx_init(WIDTH, HEIGHT, "MLX42", 0);
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->minimap_img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(mlx->mlx, mlx->img, 0, 0);
	mlx_image_to_window(mlx->mlx, mlx->minimap_img, 0, 0);
}

int	load_image(t_mlx *mlx)
{
	t_dirs *ptr;
	int		i;

	i = 0;
	ptr = get_type()->directions;
	while (ptr && i < 4)
	{
		mlx->tile[i] = mlx_load_png(ptr->path);
		if (mlx->tile[i]->width != mlx->tile[i]->height)
			return (1);
		ptr = ptr->next;
		i++;
	}
	mlx->tile[4] = mlx_load_png("image/door.png");
	if (mlx->tile[4]->width != mlx->tile[4]->height)
		return (1);
	return (0);
}

void	set_value(t_mlx *mlx)
{
	int	i;

	i = 0;
	get_type()->mlx = mlx;
	mlx->map = get_type()->map;
	mlx->movex = get_type()->x;
	mlx->movey = get_type()->y;
	while (mlx->map[i])
		i++;
	mlx->map_hight = i;
	i = 0;
	while (mlx->map[0][i])
		i++;
	mlx->map_width = i;
	mlx->movex += BLOCSIZE / 2;
	mlx->movey += BLOCSIZE / 2;
	if (mlx->map_width > mlx->map_hight)
		mlx->max = mlx->map_width;
	mlx->angle = get_type()->pa;
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (ac != 2)
		return (1);
	ft_memset(&mlx, 0, sizeof(mlx));
	if (ft_parse(*(av + 1)))
		{
			while (1);
			return (1);
		}
	
	printf("end parsing\n");
	exit(0);
	set_value(&mlx);
	load_mlx(&mlx);
	if (load_image(&mlx))
	{
		write(2, "Failed to load image\n", 21);
		mlx_terminate(mlx.mlx);
		exit(1);
	}
	mlx.start = 1;
	mlx_key_hook(mlx.mlx, dor_click, &mlx);
	mlx_loop_hook(mlx.mlx, event_win, &mlx);
	mlx_loop_hook(mlx.mlx, drow_player, &mlx);
	mlx_loop(mlx.mlx);
	mlx_terminate(mlx.mlx);
}
