/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaanni <mbaanni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:11:12 by mbaanni           #+#    #+#             */
/*   Updated: 2023/09/27 12:34:32 by mbaanni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Cub3D.h"

float dist(float px, float py, float rx, float ry)
{
    float dx;
    float dy;

    dx = rx - px;
    dy = ry - py;

    float res = sqrt((dx*dx) + (dy*dy));
    return res;
}

float   bound_angle(float angle)
{
    if (angle < 0)
        angle += 2 * PI;
    else if (angle >= 2 * PI)
        angle -= 2 * PI;
    return (angle);
}

uint32_t get_color(t_mlx *mlx,int y, int x)
{
	int pos = (y * mlx->tile[mlx->side]->width + x) * mlx->tile[mlx->side]->bytes_per_pixel;
	if (pos < 0 || pos > (mlx->tile[mlx->side]->height * (mlx->tile[mlx->side]->width*4)) - 4)
        return 0;
	return (mlx->tile[mlx->side]->pixels[pos]<<24 | mlx->tile[mlx->side]->pixels[pos+1]<<16 | mlx->tile[mlx->side]->pixels[pos+2]<<8 | mlx->tile[mlx->side]->pixels[pos+3]);
}

void    draw_block(mlx_image_t *img, int start, int end, int ray, uint32_t color)
{

    while (start < end)
    {
		mlx_put_pixel(img, ray, start, color);
        start++;
    }
}

void    draw_wall(t_mlx *mlx, t_ray *ray, int r, float distray, float angle_step, float ra)
{
    float wall_strip_hight;
	uint32_t color;
    if (distray < 0)
        distray = 1;
    // //fish eyes
    distray = cos(30*PI/180-(r*angle_step))*distray;
    //wall_strip_hight = (BLOCSIZE/distray) * (((float)HEIGHT/2)/(tan(30*PI/180)));
	wall_strip_hight = BLOCSIZE/distray * 1200;
    float	wall_start = (HEIGHT / 2) - (wall_strip_hight / 2);
	float	wall_end = (HEIGHT / 2) + (wall_strip_hight / 2);
	if (wall_start < 0)
		wall_start = 0;
	int texter_y;
	int texter_x = mlx->offset * ((int)(mlx->tile[mlx->side]->width / BLOCSIZE));
    if (mlx->side == TOP || mlx->side == RIGHT)
        texter_x = mlx->tile[mlx->side]->width - texter_x;
    draw_block(mlx->img, 0, HEIGHT/2, r, 0x45b3e0ff);
	while (wall_start < wall_end && wall_start < HEIGHT)
	{
		texter_y = (1.0-(wall_end - wall_start)/wall_strip_hight)*(mlx->tile[mlx->side]->height);
		color = get_color(mlx,texter_y, texter_x);
		mlx_put_pixel(mlx->img, r, wall_start, color);
		wall_start++;
    }
    draw_block(mlx->img, wall_end, HEIGHT, r, 0xffffff00);
}

void draw_ray(t_mlx *mlx)
{
    t_ray	ray;
    int		r;
    float	ra;
	float	angle_step;
    float	distray;

    r = -1;
    mlx->ray = &ray;
    angle_step = (field_of_view * (PI/180)) / WIDTH;
    ra = mlx->angle - ((float)field_of_view / 2) * (PI/180) + angle_step * 0.5;
    while(++r < WIDTH)
    {
		ra = bound_angle(ra);
		calculate_horizontal(ra, mlx, &ray);
		calculate_vertical(ra, mlx, &ray);
		small_dist(&ray, mlx, &distray);
		draw_line(mlx->minimap_img, mlx->movex, mlx->movey, ray.rx, ray.ry,0x00ff00FF);
        draw_wall(mlx, &ray, r, distray, angle_step, ra);
		ra += angle_step;
    }
}

void    ffps(void *ptr, mlx_image_t *txt)
{
    mlx_t *mlx = (mlx_t*)ptr;
    mlx_put_pixel(txt, 0, 0, 0xff0000ff);
}

void     draw_miniplayer(t_mlx *mlx)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < 24)
    {
        x = 0;
        while (x < 24)
        {
            if (calculate_dist(mlx->movex-4, mlx->movey-4, mlx->movex+x, mlx->movey+y)<=18)
                put_on_minimap(mlx, (mlx->movex) + x,(mlx->movey) + y, 0xff0000ff);
            x++;
        }
        y++;
    }
}

void    drow_player(void *ptr)
{
	t_mlx   *mlx;
    int     fps;

	mlx = (t_mlx*)ptr;
	if (mlx->start)
    {
        ft_clean(mlx);
        fps = mlx->mlx->delta_time * 1000;
        if (mlx->txt)
        {
            mlx_delete_image(mlx->mlx, mlx->txt);
            mlx->txt = 0;
        }
        mlx->txt = mlx_put_string(mlx->mlx, ft_itoa(fps),WIDTH/2,0);
        if (mlx->txt)
            ffps(mlx->mlx,mlx->txt);
		drow_map(mlx);
		draw_ray(mlx);
        //draw_miniplayer(mlx);
		mlx->start = 0;
	}
}
