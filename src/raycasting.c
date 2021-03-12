/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/12 18:30:10 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	recognize_texture(t_all *all, int side)
{
	double ang;
	
	ang = vector_angle(&all->norm, &all->ray);
	all->active = &all->ea;

	if (side == 0)
	{
		if (ang >= 180.0f && ang <= 360.0f)
			all->active = &all->no;
		else
			all->active = &all->so;
	}	
	else
	{
		if (ang >= 90.0f && ang <= 270.0f)
			all->active = &all->we;
		else
			all->active = &all->ea;
	}
}

void    write_pixel_to_img(t_img *img, int x, int y, int color)
{
    char    *dst;
	int     offset;
	
	offset = y * img->len + x * (img->bpp / 8);
    dst = img->addr + offset;
    *(unsigned int*)dst = color;
}

int		get_color_from_params(t_clr *clr)
{
	return (0L | clr->val[0] << 16 | clr->val[1] << 8 | clr->val[2]);	
}

void	set_background(t_all *all)
{
	int i;
 	int j;
	int color;

 	i = 0;
	color = get_color_from_params(&all->map->f);
	while (i < all->map->h)
 	{
 		j = 0;
 		if (i == all->map->h / 2)
		 	color = get_color_from_params(&all->map->c);
		while (j < all->map->w)
 		{
			all->buf[i][j] = color;
 			//write_pixel_to_img(&all->img, j, i, color);
			j++;
		}
 		i++;
 	}	
}

int		render(t_all *all)
{
	set_background(all);
	raycasting(all);
	mlx_put_image_to_window(all->mlx, all->win, all->img.img, 0, 0);
 	return (0);
}

void	init_vectors(t_all *all, int i, int j)
{
	if (all->map->arr[i][j] == 'N')
	{
		all->angle = 270;
		vector_init(&all->dir, -1.0, 0.0);
		vector_init(&all->plane, 0.0, 0.66);
		
	}
	if (all->map->arr[i][j] == 'E')
	{
		all->angle = 0;
		vector_init(&all->dir, 0.0, 1.0);
		vector_init(&all->plane, 0.66, 0);
	}
	if (all->map->arr[i][j] == 'W')
	{
		all->angle = 180;
		vector_init(&all->dir, 0.0, -1.0);
		vector_init(&all->plane, -0.66, 0);
		
	}
	if (all->map->arr[i][j] == 'S')
	{
		all->angle = 90;
		vector_init(&all->dir, 1.0, 0.0);
		vector_init(&all->plane, 0.0, -0.66);
	}
	printf("x = %.3f y= %.3f\n", i + 0.5, j + 0.5);
	printf("dir[%.3f %.3f]\n", all->dir.x, all->dir.y);
}

void	init_coord(t_all *all)
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
				init_vectors(all, i, j);
				vector_init(&all->pos, i + 0.5, j + 0.5);
			}
 			j++;
 		}
 		i++;
	}
	vector_init(&all->norm, 0.0, 1.0);	
}

void	start_main_loop(t_map *map)
{
	t_all all;
	
	all.map = map;
	init_all(&all);
	mlx_hook(all.win, 2, 1L<<0, key_press, &all);
	mlx_hook(all.win, 3, 1L<<1, key_release, &all);
	mlx_loop_hook(all.mlx, render, &all);
	mlx_loop(all.mlx);
}

void	init_all(t_all *all)
{
	all->m_speed = 0.111f;
	all->r_angle = 0.066f;
	
	all->buf = (int **)malloc((sizeof(int *)) * all->map->h);
	int i = 0;
	while (i < all->map->h)
	{
		all->buf[i] = (int *)malloc(sizeof(int) * all->map->w);
		i++;
	}

	init_window(all);	
	init_img(all, &all->img);
	init_keys(all);
	init_coord(all);
	init_textures(all);
}

//void  raycasting(t_all *all)
//{
//	for (int x = 0; x < all->map->w; x++)
//	{	
//		//calculate ray position and direction
//		 //x-coordinate in camera space
//		double cameraX = 2 * x / (double)all->map->w - 1;
//		all->ray.x = all->dir.x + all->plane.x * cameraX;
//		all->ray.y = all->dir.y + all->plane.y * cameraX;
		
//		//which box of the map we're in
//		int mapX = (int)all->pos.x;
//		int mapY = (int)all->pos.y;

//		//length of ray from current position to next x or y-side
//		double sideDistX;
//		double sideDistY;

//		//length of ray from one x or y-side to next x or y-side
//		double deltaDistX = fabs(1 / all->ray.x);
//		double deltaDistY = fabs(1 / all->ray.y);
//		double perpWallDist;

//		//what direction to step in x or y-direction (either +1 or -1)
//		int stepX;
//		int stepY;

//		int hit = 0; //was there a wall hit?
//		int side; //was a NS or a EW wall hit?

//		//calculate step and initial sideDist
//		if(all->ray.x < 0)
//		{
//			stepX = -1;
//			sideDistX = (all->pos.x - mapX) * deltaDistX;
//		}
//		else
//		{
//			stepX = 1;
//			sideDistX = (mapX + 1.0 - all->pos.x) * deltaDistX;
//		}
		
//		if (all->ray.y < 0)
//		{
//			stepY = -1;
//			sideDistY = (all->pos.y - mapY) * deltaDistY;
//		}
//		else
//		{
//			stepY = 1;
//			sideDistY = (mapY + 1.0 - all->pos.y) * deltaDistY;
//		}

//		//perform DDA
//		while (hit == 0)
//		{
//			//jump to next map square, OR in x-direction, OR in y-direction
//			if (sideDistX < sideDistY)
//			{
//				sideDistX += deltaDistX;
//				mapX += stepX;
//				side = 0;
//			}
//			else
//			{
//				sideDistY += deltaDistY;
//				mapY += stepY;
//				side = 1;
//			}
//			//Check if ray has hit a wall
//			if (all->map->arr[mapX][mapY] == '1') 
//				hit = 1;
//		}

//		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!
//		//printf("%d %d\n", mapX, mapY);
//		if (side == 0)
//			perpWallDist = (mapX - all->pos.x + (1 - stepX) / 2) / all->ray.x;
//		else
//			perpWallDist = (mapY - all->pos.y + (1 - stepY) / 2) / all->ray.y;

//		//Calculate height of line to draw on screen
//		int lineHeight = (int)(all->map->h / perpWallDist);
//		// if (lineHeight > all->map->h)
//		// 	lineHeight = all->map->h;
//		//calculate lowest and highest pixel to fill in current stripe
//		int drawStart = -lineHeight / 2 + all->map->h / 2;
//		if (drawStart < 0)
//			drawStart = 0;
		
//		int drawEnd = lineHeight / 2 + all->map->h / 2;
//		if (drawEnd > all->map->h)
//			drawEnd = all->map->h;

//		//texturing calculations
//		// int texNum = all->map->arr[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
//		recognize_texture(all, side);
//		 //calculate value of wallX
//		double wallX; //where exactly the wall was hit
//		if (side == 0)
//			wallX = all->pos.y + perpWallDist * all->ray.y;
//		else
//			wallX = all->pos.x + perpWallDist * all->ray.x;
//		wallX -= floor((wallX));

//		//x coordinate on the texture
//		int texX = (int)(wallX * (double)all->active->w);
//		//printf("texX:%d all->no.w:%d\n", texX, all->no.w);
//		if (side == 0 && all->ray.x > 0) 
//			texX = all->active->w - texX - 1;
//		if (side == 1 && all->ray.y < 0)
//			texX = all->active->w - texX - 1;

//		// // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
//		// // How much to increase the texture coordinate per screen pixel		
//		double step = 1.0 * all->active->w / lineHeight;
//		// Starting texture coordinate
//		double texPos = (drawStart - all->map->h / 2 + lineHeight / 2) * step;

//		for (int y = drawStart; y < drawEnd; y++)
//		{
//		 	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
//			int texY = (int)texPos; //& (all->active->h - 1);
//		 	texPos += step;
		 	
//			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
//			int offset = texY * all->active->w + texX;
//			unsigned int *dst = (unsigned int *)all->active->img.addr + offset;

//		 	// if (side == 1)
//		 	// 	*dst = *dst & 0xFF808080;
//			write_pixel_to_img(&all->img, x, y, *dst);
//		}
//	}
//}

void draw_walls(t_all *all)
{
	char *dst;
	for (int i = 0; i < all->map->h; i++)
	{
		for (int j = 0; j < all->map->w; j++)
		{
			int offset = i * all->img.len + j;
			dst = all->img.addr + offset;
			*dst = all->buf[i][j];
		}
	}
}

void  raycasting(t_all *all)
{
	for (int x = 0; x < all->map->w; x++)
	{	
		//calculate ray position and direction
		//x-coordinate in camera space
		double cameraX = 2 * x / (double)all->map->w - 1;
	
		all->ray.x = all->dir.x + all->plane.x * cameraX;
		all->ray.y = all->dir.y + all->plane.y * cameraX;

		//which box of the map we're in
		int mapX = (int)all->pos.x;
		int mapY = (int)all->pos.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = fabs(1 / all->ray.x);
		double deltaDistY = fabs(1 / all->ray.y);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?

		//calculate step and initial sideDist
		if (all->ray.x < 0)
		{
			stepX = -1;
			sideDistX = (all->pos.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - all->pos.x) * deltaDistX;
		}
		
		if (all->ray.y < 0)
		{
			stepY = -1;
			sideDistY = (all->pos.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - all->pos.y) * deltaDistY;
		}
		int count = 0;
		//perform DDA
		while (hit == 0)
		{
			count++;
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

		//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!
		

		//if (side == 0) ????
			//perpWallDist = vector_len(&all->ray) * sin(90 - vector_angle(&all->dir, &all->ray));
		//else
		//	perpWallDist = ;
		//printf("pwd:%.3f\n", perpWallDist);

		if (side == 0)
			perpWallDist = (mapX - all->pos.x + (1 - stepX) / 2) / all->ray.x;
		else
			perpWallDist = (mapY - all->pos.y + (1 - stepY) / 2) / all->ray.y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(all->map->h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + all->map->h / 2;
		if (drawStart < 0)
			drawStart = 0;
		
		int drawEnd = lineHeight / 2 + all->map->h / 2;
		if (drawEnd > all->map->h)
			drawEnd = all->map->h;

		//texturing calculations
		recognize_texture(all, side);
		
		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = all->pos.y + perpWallDist * all->ray.y;
		else
			wallX = all->pos.x + perpWallDist * all->ray.x;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)all->active->w);
		
		if (side == 0 && all->ray.x > 0) 
			texX = all->active->w - texX - 1;
		if (side == 1 && all->ray.y < 0)
			texX = all->active->w - texX - 1;

		// // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
		// // How much to increase the texture coordinate per screen pixel
		
		double step = 1.0 * all->active->w / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - all->map->h / 2 + lineHeight / 2) * step;

		for (int y = drawStart; y < drawEnd; y++)
		{
		 	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int)texPos & (all->active->h - 1);
		 	texPos += step;
		 	
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			int offset = texY * all->active->w + texX;
			unsigned int dst = *((unsigned int *)all->active->img.addr + offset);
			all->buf[y][x] = dst;
			write_pixel_to_img(&all->img, x, y, dst);
			//write_pixel_to_img(&all->img, x + 1, y, *dst);
		}
	}
	draw_walls(all);
}
