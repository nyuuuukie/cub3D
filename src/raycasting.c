/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/09 01:37:18 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	know_text(t_all *all, double x, double y)
{
	t_vector ray;
	double angle;
	vector_init(&ray, x, y);
	angle = vector_angle(&all->norm, &ray) * 180 / M_PI;
	//printf("v1(%.2f:%.2f) v2(%.2f:%.2f), angle: %.2f\n", all->dir.x, all->dir.y, norm.x, norm.y, vector_angle(&norm, &all->dir) * 180 / M_PI);
	
	all->active = &all->no;
	if (angle > 45.0f && angle <= 135.0f)
	{
		if (all->dir.x > 0.0f)
			all->active = &all->ea;
		else
			all->active = &all->we;
	}
	if (angle > 135.0f && angle <= 180.0f)
		all->active = &all->so;
}

void	rotate(t_all *all, int sign)
{
	double oldDirX = all->dir.x;
	all->dir.x = all->dir.x * cos(sign * all->rotSpeed) - all->dir.y * sin(sign * all->rotSpeed);
	all->dir.y = oldDirX * sin(sign * all->rotSpeed) + all->dir.y * cos(sign * all->rotSpeed);

	double oldPlaneX = all->plane.x;
	all->plane.x = all->plane.x * cos(sign * all->rotSpeed) - all->plane.y * sin(sign * all->rotSpeed);
	all->plane.y = oldPlaneX * sin(sign * all->rotSpeed) + all->plane.y * cos(sign * all->rotSpeed);

	//know_text(all);
}

void	move(t_all *all, int sign)
{
	t_vector	new;
	char		**map;

	//printf("op(%.2f:%.2f) dir(%.2f:%.2f)", all->pos.x, all->pos.y, all->dir.x, all->dir.y);
	map = all->map->arr;
	new.x = all->pos.x + (sign * all->dir.x * all->moveSpeed);
	new.y = all->pos.y + (sign * all->dir.y * all->moveSpeed);
	if (map[(int)new.x][(int)all->pos.y] != '1')
		all->pos.x = new.x;
	if (map[(int)all->pos.x][(int)new.y] != '1')
		all->pos.y = new.y;
	//printf(" np(%.2f:%.2f)\n", all->pos.x, all->pos.y);
}

int	stop_engine(void *ptr)
{
	t_all *all;

	all = (t_all *)ptr;
	printf("Stopped! %d\n", all->map->r_width);
	//Clean everything
	exit(0);
}

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;
	int     offset;
	
	offset = y * data->line_length + x * (data->bits_per_pixel / 8);
    dst = data->addr + offset;
    *(unsigned int*)dst = color;
}

void	set_scale(t_all *all)
{
 	int scale_w;
 	int scale_h;

 	#ifdef SCALE
 		scale_w = 1;
 		scale_h = 1;
 		all->scale = SCALE * scale_w * scale_h;
 	#else
 		scale_w = (all->map->r_width - 2 * all->padding) / all->map->cols;
 		scale_h = (all->map->r_height - 2 * all->padding) / all->map->rows;
 		all->scale = scale_h < scale_w ? scale_h : scale_w; 
 	#endif
}

 float	get_radian(float angle)
 {
 	return angle * M_PI / 180;
 }

 void	throw_ray(t_all *all, t_plr *ray, int color)
 {
 	float radian = get_radian(ray->start);

 	while (all->map->arr[(int)(ray->y / all->scale)][(int)(ray->x / all->scale)] != '1')
 	{
 		ray->x += cos(radian);
 		ray->y += sin(radian);
 		my_mlx_pixel_put(all->img, ray->x, ray->y, color);
 	}
 }

void	ft_cast_rays(t_all *all, int color)
{
 	t_plr	ray = *all->plr;
 	ray.start = ray.dir - (FOV / 2);
 	ray.end = ray.dir + (FOV / 2);
 
 	while (ray.start <= ray.end)
 	{
 		ray.x = all->plr->x;
 		ray.y = all->plr->y;

 		throw_ray(all, &ray, color);
 		ray.start += (float)FOV / (float)RPA;
 	}
}

 void	put_cell(t_all *all, t_data *img, int x0, int y0, int color)
 {
 	int i;
 	int j;

 	i = 0;
 	while (i < all->scale)
 	{
 		j = 0;
 		while (j < all->scale)
 		{
 			my_mlx_pixel_put(img, x0 + j, y0 + i, color);
 			j++;
 		}
 		i++;
 	}
 }

 void	put_minimap(t_all *all, int color)
 {
 	//static int raycolor = 0x00ADADAD;
 	int i;
 	int j;

 	i = 0;
 	while (i < all->map->rows)
 	{
 		j = 0;
 		while (j < all->map->cols + 1)
 		{
 			if (all->map->arr[i][j] == '1')
 				put_cell(all, all->img, j * all->scale, i * all->scale, color);
 			else if (all->map->arr[i][j] == '2')
 				put_cell(all, all->img, j * all->scale, i * all->scale, 0x00FF0000);
 			else
 				put_cell(all, all->img, j * all->scale, i * all->scale, 0x00FFFFFF);
 			j++;  
 		}
 		i++;
 	}
 	put_cell(all, all->img, all->pos.y * all->scale, all->pos.x * all->scale, 0x00FFFF00);
}


int	get_color(t_clr *clr)
{
	int color;
	
	color = 0L | clr->val[0] << 16 | clr->val[1] << 8 | clr->val[2];
	return color;
}

void	color_pane(t_all *all)
{
	int i;
 	int j;
	int color;

 	i = 0;
	color = get_color(&all->map->f);
	while (i < all->map->r_height)
 	{
 		j = 0;
 		if (i == all->map->r_height / 2)
		 	color = get_color(&all->map->c);
		while (j < all->map->r_width)
 		{
 			my_mlx_pixel_put(all->img, j, i, color);
			j++;
		}
 		i++;
 	}	
}

 int 	render(t_all *all)
 {
    color_pane(all);
	raycasting(all);
	// put_minimap(all, 0x00242424);
 	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
 	return (0);
 }

int		key_hook(int keycode, t_all *all)
{
	//mlx_sync(MLX_SYNC_IMAGE_WRITABLE, &all);
	mlx_do_sync(all->mlx);
	//printf("key: %d\n", keycode);
	if (keycode == KEY_W)
		move(all, 1);
	else if (keycode == KEY_S)
		move(all, -1);
	else if (keycode == KEY_ESC)
		stop_engine(all);
	else if (keycode == KEY_LEFT)
		rotate(all, -1);
	else if (keycode == KEY_RIGHT)
		rotate(all, 1);
	return (0);
}

void	setup_textures(t_all *all)
{
	t_texture *no;
	t_texture *so;
	t_texture *we;
	t_texture *ea;
	
	no = &all->no;
	so = &all->so;
	we = &all->we;
	ea = &all->ea;
	
	no->path = ft_strdup(all->map->NO_path);
	so->path = ft_strdup(all->map->SO_path);
	we->path = ft_strdup(all->map->EA_path);
	ea->path = ft_strdup(all->map->WE_path);
	
	no->img = mlx_xpm_file_to_image(all->mlx, no->path, &no->w, &no->h);
	so->img = mlx_xpm_file_to_image(all->mlx, so->path, &so->w, &so->h);
	we->img = mlx_xpm_file_to_image(all->mlx, we->path, &we->w, &we->h);
	ea->img = mlx_xpm_file_to_image(all->mlx, ea->path, &ea->w, &ea->h);

	no->addr = mlx_get_data_addr(no->img, &no->bits_per_pixel, &no->line_length, &no->endian);
	so->addr = mlx_get_data_addr(so->img, &so->bits_per_pixel, &so->line_length, &so->endian);
	we->addr = mlx_get_data_addr(we->img, &we->bits_per_pixel, &we->line_length, &we->endian);
	ea->addr = mlx_get_data_addr(ea->img, &ea->bits_per_pixel, &ea->line_length, &ea->endian);
	
	if (!no->img || !so->img || !we->img || !ea->img)
		throw_error(ERR_TEXTURE_FAIL, 0);
}

int		check_screen_size(t_all *all)
{
	int current_width;
	int current_height;

	mlx_get_screen_size(all->mlx, &current_width, &current_height);
	if (all->map->r_height > current_height)
		all->map->r_height = current_height;
	if (all->map->r_width > current_width)
		all->map->r_width = current_width;
	return (0);	
}


void	init_dir_vector(t_all *all, int i, int j)
{
	if (all->map->arr[i][j] == 'N')
	{
		vector_init(&all->dir, 0.0, -1.0);
		vector_init(&all->plane, 0.66, 0);
	}
	if (all->map->arr[i][j] == 'E')
	{
		vector_init(&all->dir, 1.0, 0.0);
		vector_init(&all->plane, 0.0, -0.66);
	}
	if (all->map->arr[i][j] == 'W')
	{
		vector_init(&all->dir, -1.0, 0.0);
		vector_init(&all->plane, 0.0, 0.66);
	}
	if (all->map->arr[i][j] == 'S')
	{
		vector_init(&all->dir, 0.0, 1.0);
		vector_init(&all->plane, -0.66, 0);
	}
	//printf("x = %.3f y= %.3f\n", i + 0.5, j + 0.5);
	vector_init(&all->pos, i + 0.5, j + 0.5);
}

void	init_coord_plr(t_all *all)
{
 	int i;
 	int j;

 	i = 1;
 	while (i < all->map->rows)
 	{
 		j = 1;
 		while (j < all->map->cols + 1)
 		{	
			if (ft_strchr("NSWE", all->map->arr[i][j]))
 			{
				init_dir_vector(all, i, j);
			}
 			j++;
 		}
 		i++;
	}
	vector_init(&all->norm, 0.0, -1.0);	
}

void	init_raycast(t_map *map)
{
	t_all all;
	t_data img;

	all.map = map;
	all.isEnabled = 1;
	init_coord_plr(&all);

	all.mlx = mlx_init();
	all.mlx_win = mlx_new_window(all.mlx, map->r_width, map->r_height, "cub3D");
	check_screen_size(&all);
	
	img.img = mlx_new_image(all.mlx, map->r_width, map->r_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	all.img = &img;
	
	//Set default values
	set_scale(&all);
	setup_textures(&all);

	all.moveSpeed = 0.084; //the constant value is in squares/second
	all.rotSpeed = 0.084; //the constant value is in radians/second
	
	mlx_hook(all.mlx_win, 2, 1L, key_hook, &all);
	mlx_loop_hook(all.mlx, render, &all);
	//mlx_hook(all.mlx_win, 17, 1, stop_engine, &all);
	mlx_loop(all.mlx);
}

void  raycasting(t_all *all)
{
		for (int x = 0; x < all->map->r_width; x++)
		{	
			//calculate ray position and direction
			double cameraX = 2 * x / (double)all->map->r_width - 1; //x-coordinate in camera space
			double rayDirX = all->dir.x + all->plane.x * cameraX;
			double rayDirY = all->dir.y + all->plane.y * cameraX;

			//which box of the map we're in
			int mapX = (int)all->pos.x;
			int mapY = (int)all->pos.y;

			//length of ray from current position to next x or y-side
			double sideDistX;
			double sideDistY;

			//length of ray from one x or y-side to next x or y-side
			double deltaDistX = fabs(1 / rayDirX);
			double deltaDistY = fabs(1 / rayDirY);
			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?

			//calculate step and initial sideDist
			if(rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (all->pos.x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - all->pos.x) * deltaDistX;
			}
			if(rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (all->pos.y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - all->pos.y) * deltaDistY;
			}

			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, OR in x-direction, OR in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (all->map->arr[mapX][mapY] == '1') 
					hit = 1;
			}

			//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
			
			//printf("%d %d\n", mapX, mapY);
			if (side == 0)
				perpWallDist = (mapX - all->pos.x + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - all->pos.y + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(all->map->r_height / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + all->map->r_height / 2;
			if (drawStart < 0)
				drawStart = 0;
			
			int drawEnd = lineHeight / 2 + all->map->r_height / 2;
			if (drawEnd >= all->map->r_height)
				drawEnd = all->map->r_height - 1;

			//texturing calculations
			// int texNum = all->map->arr[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
			know_text(all, rayDirX, rayDirY);
			 //calculate value of wallX
			 double wallX; //where exactly the wall was hit
			 if (side == 0)
			 	wallX = all->pos.y + perpWallDist * rayDirY;
			 else
			 	wallX = all->pos.x + perpWallDist * rayDirX;
			 wallX -= floor((wallX));

			//x coordinate on the texture
			 int texX = (int)(wallX * (double)all->active->w);
				//printf("texX:%d all->no.w:%d\n", texX, all->no.w);
			 if (side == 0 && rayDirX > 0) 
			 	texX = all->active->w - texX - 1;
			 if (side == 1 && rayDirY < 0)
			 	texX = all->active->w - texX - 1;

			// // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
			// // How much to increase the texture coordinate per screen pixel
			
			 double step = 1.0 * all->active->w / lineHeight;
			 // Starting texture coordinate
			 double texPos = (drawStart - all->map->r_height / 2 + lineHeight / 2) * step;
			//printf("step:%.3f %d\n", step, lineHeight);
			for (int y = drawStart; y < drawEnd; y++)
			{
			 	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			 	
				int texY = (int)texPos;//& (all->no.h - 1);
			 	texPos += step;
			 	//int color = (all->no.img + all->no.h * texY + texX);
			 	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
				int offset = texY * all->active->w + texX;
				unsigned int *dst = (unsigned int *)all->active->addr + offset;

			 	//printf("%d %d %d\n", texX, texY, *dst);
				// if (side == 1)
			 	//	color = (color >> 1) & 8355711;
				my_mlx_pixel_put(all->img, x, y, *dst);
	
				 // buffer[y][x] = color;
			}
			//mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
    	}
}