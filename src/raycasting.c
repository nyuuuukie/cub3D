/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 20:00:48 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/08 13:14:52 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	know_text(t_all *all)
{
	t_vector norm;
	double angle;

	vector_init(&norm, 0.0, -1.0);
	angle = vector_angle(&norm, &all->dir) * 180 / M_PI;
	printf("v1(%.2f:%.2f) v2(%.2f:%.2f), angle: %.2f\n", all->dir.x, all->dir.y, norm.x, norm.y, vector_angle(&norm, &all->dir) * 180 / M_PI);
	
	if (angle > 0.0f && angle <= 45.0f)
		printf("NO!\n");
	if (angle > 45.0f && angle <= 135.0f)
	{
		if (all->dir.x > 0.0f)
			printf("EA!\n");
		else
			printf("WE: ");
	}
	if (angle > 135.0f && angle <= 180.0f)
		printf("SO!\n");
}

void	rotate(t_all *all, int sign)
{
	double oldDirX = all->dir.x;
	all->dir.x = all->dir.x * cos(sign * all->rotSpeed) - all->dir.y * sin(sign * all->rotSpeed);
	all->dir.y = oldDirX * sin(sign * all->rotSpeed) + all->dir.y * cos(sign * all->rotSpeed);

	double oldPlaneX = all->plane.x;
	all->plane.x = all->plane.x * cos(sign * all->rotSpeed) - all->plane.y * sin(sign * all->rotSpeed);
	all->plane.y = oldPlaneX * sin(sign * all->rotSpeed) + all->plane.y * cos(sign * all->rotSpeed);

	know_text(all);
}

void	move(t_all *all, int sign)
{
	t_vector	new;
	char		**map;

	printf("op(%.2f:%.2f) dir(%.2f:%.2f)", all->pos.x, all->pos.y, all->dir.x, all->dir.y);
	map = all->map->arr;
	new.x = all->pos.x + (sign * all->dir.x * all->moveSpeed);
	new.y = all->pos.y + (sign * all->dir.y * all->moveSpeed);
	if (map[(int)new.x][(int)all->pos.y] != '1')
		all->pos.x = new.x;
	if (map[(int)all->pos.x][(int)new.y] != '1')
		all->pos.y = new.y;
	printf(" np(%.2f:%.2f)\n", all->pos.x, all->pos.y);
}

void	stop_engine(t_all *all)
{
	printf("Stopped! %d\n", all->map->r_width);
	all->isEnabled = 0;
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

 int 	render(t_all *all, t_data *img)
 {
    put_minimap(all, 0x00242424);
 	mlx_put_image_to_window(all->mlx, all->mlx_win, img->img, 0, 0);
 	return (0);
 }

int		key_hook(int keycode, t_all *all)
{
	mlx_do_sync(all->mlx);
	if (keycode == KEY_W)
		move(all, 1);
	else if (keycode == KEY_S)
		move(all, -1);
	else if (keycode == KEY_ESC)
		stop_engine(all);
	else if (keycode == KEY_LEFT)
		rotate(all, 1);
	else if (keycode == KEY_RIGHT)
		rotate(all, -1);
	mlx_put_image_to_window(all->mlx, all->mlx_win, all->img->img, 0, 0);
	//render(all, all->img);
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
	vector_init(&all->pos, j + 0.5, i + 0.5);
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
}

void  raycasting(t_map *map)
{
	t_all all;
	t_data img;

	all.map = map;
	all.isEnabled = 1;
	init_coord_plr(&all);
	//vector_init(&all.pos, 22, 11.5);
	//vector_init(&all.dir, -1.0, 0.0);
	//vector_init(&all.plane, 0.0, 0.66);
	// all.pos.x = 22; all.pos.y = 11.5;
	// all.dir.x = -1.0; all.dir.y = 0.0;
	// all.plane.x = 0.0; all.plane.y = 0.66;
  
	// double time = 0; //time of current frame
	// double oldTime = 0; //time of previous frame

	// std::vector<Uint32> texture[8];
	// for (int i = 0; i < 8; i++) 
    // 	texture[i].resize(texWidth * texHeight);

	all.mlx = mlx_init();
	all.mlx_win = mlx_new_window(all.mlx, map->r_width, map->r_height, "cub3D");
	check_screen_size(&all);
	
	img.img = mlx_new_image(all.mlx, map->r_width, map->r_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	all.img = &img;
	
	//Set default values
	set_scale(&all);
	// init_coord_plr(&all);

	setup_textures(&all);

  	//start the main loop
	while (all.isEnabled)
	{
		for (int x = 0; x < all.map->r_width; x++)
		{
			//calculate ray position and direction
			double cameraX = 2 * x / (double)all.map->r_width - 1; //x-coordinate in camera space
			double rayDirX = all.dir.x + all.plane.x * cameraX;
			double rayDirY = all.dir.y + all.plane.y * cameraX;

			//which box of the map we're in
			int mapX = (int)all.pos.x;
			int mapY = (int)all.pos.y;

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
				sideDistX = (all.pos.x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - all.pos.x) * deltaDistX;
			}
			if(rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (all.pos.y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - all.pos.y) * deltaDistY;
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
				if (map->arr[mapX][mapY] > '0') 
					hit = 1;
			}

			//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
			if (side == 0)
				perpWallDist = (mapX - all.pos.x + (1 - stepX) / 2) / rayDirX;
			else
				perpWallDist = (mapY - all.pos.y + (1 - stepY) / 2) / rayDirY;

			//Calculate height of line to draw on screen
			int lineHeight = (int)(all.map->r_height / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + all.map->r_height / 2;
			if (drawStart < 0)
				drawStart = 0;
			
			int drawEnd = lineHeight / 2 + all.map->r_height / 2;
			if (drawEnd >= all.map->r_height)
				drawEnd = all.map->r_height - 1;

			//texturing calculations
			// int texNum = all.map->arr[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

			 //calculate value of wallX
			 double wallX; //where exactly the wall was hit
			 if (side == 0)
			 	wallX = all.pos.y + perpWallDist * rayDirY;
			 else
			 	wallX = all.pos.x + perpWallDist * rayDirX;
			 wallX -= floor((wallX));

			//x coordinate on the texture
			 int texX = (int)(wallX * (double)all.no.w);
			
			 if (side == 0 && rayDirX > 0) 
			 	texX = all.no.w - texX - 1;
			 if (side == 1 && rayDirY < 0)
			 	texX = all.no.w - texX - 1;


			// // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
			// // How much to increase the texture coordinate per screen pixel
			
			 double step = 1.0 * all.no.h / lineHeight;
			 // Starting texture coordinate
			 double texPos = (drawStart - all.map->r_height / 2 + lineHeight / 2) * step;

			 for (int y = drawStart; y < drawEnd; y++)
			 {
			 	// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			 	int texY = (int)texPos & (all.no.h - 1);
			 	texPos += step;
			 	int* color = (int *)(all.no.img + all.no.h * texY + texX);
			 	//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			 	
				 if (side == 1)
			 		color = (color >> 1) & 8355711;
			 	
				 my_mlx_pixel_put(all.img, x, y, *color);
			 	// buffer[y][x] = color;
			 }
    	}

		// drawBuffer(buffer[0]);


				// DONT NEED ? 
				// for(int y = 0; y < all.map->r_height; y++)
				// 	for(int x = 0; x < all.map->r_width; x++)
				// 		buffer[y][x] = 0;
				
		
			//timing for input and FPS counter
			// oldTime = time;
			// time = getTicks();
			// double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
			// print(1.0 / frameTime); //FPS counter
		
		// redraw();

		//speed modifiers
		all.moveSpeed = 0.084; //the constant value is in squares/second
		all.rotSpeed = 0.084; //the constant value is in radians/second
	
		mlx_hook(all.mlx_win, 2, 1L, key_hook, &all);
		mlx_loop(all.mlx);
	
		// readKeys();
		//move forward if no wall in front of you
		// if(keyDown(SDLK_UP))
		// {
		// 	if (all.map->arr[(int)(all.pos.x + all.dir.x * moveSpeed)][(int)all.pos.y] == '0')
		// 		all.pos.x += all.dir.x * moveSpeed;
		// 	if (all.map->arr[(int)(pos.x)][(int)(pos.y + dir.y * moveSpeed)] == '0')
		// 		all.pos.y += all.dir.y * moveSpeed;
		// }
		// //move backwards if no wall behind you
		// if(keyDown(SDLK_DOWN))
		// {
		// 	if (all.map->arr[(int)(pos.x - dir.x * moveSpeed)][(int)pos.y] == '0')
		// 		pos.x -= dir.x * moveSpeed;
		// 	if (all.map->arr[(int)(pos.x)][(int)(pos.y - dir.y * moveSpeed)] == '0')
		// 		pos.y -= dir.y * moveSpeed;
		// }
		//rotate to the right
		// if(keyDown(SDLK_RIGHT))
		// {
		// 	//both camera direction and camera plane must be rotated
		// 	double oldDirX = dirX;
		// 	dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		// 	dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);

		// 	double oldPlaneX = planeX;
		// 	planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		// 	planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
		// }
		// //rotate to the left
		// if(keyDown(SDLK_LEFT))
		// {
		// 	//both camera direction and camera plane must be rotated
		// 	double oldDirX = dirX;
		// 	dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		// 	dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);

		// 	double oldPlaneX = planeX;
		// 	planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		// 	planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
		// }
		// if(keyDown(SDLK_ESCAPE))
		// {
		//   break;
		// }
	}
}