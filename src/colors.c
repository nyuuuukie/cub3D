/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:16:02 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/25 17:41:33 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		color_from_prm(t_clr *clr)
{
	return (0L | clr->val[0] << 16 | clr->val[1] << 8 | clr->val[2]);	
}

int		color_from_txt(t_texture *txt, int x, int y)
{
	t_img *img;

	img = &txt->img;
	if (x >= 0 && y >= 0 && x <= txt->w && y <= txt->h)
		return (*(int *)(img->addr + y * img->len + x * (img->bpp / 8))); 
	else
		return (0x00000000);
}

int		color_make_darker(double perc, int color)
{
 	int r;
	int g;
	int b;

	r = ((color & 0x00FF0000) >> 16) * (1 - perc);
	g = ((color & 0x0000FF00) >> 8) * (1 - perc);
	b = ((color & 0x000000FF) >> 0) * (1 - perc);	
	r += (r < MIN_R) * (MIN_R - r);
	g += (g < MIN_G) * (MIN_G - g);
	b += (b < MIN_B) * (MIN_B - b);
	return ((color & 0xFF000000) | (r << 16) | (g << 8) | b);
}

int		color_make_lighter(double perc, int color)
{
 	int r;
	int g;
	int b;

	r = ((color & 0x00FF0000) >> 16) * (1 + perc);
	g = ((color & 0x0000FF00) >> 8) * (1 + perc);
	b = ((color & 0x000000FF) >> 0) * (1 + perc);	
	r -= (r > MAX_R) * (r - MAX_R);
	g -= (g > MAX_G) * (g - MAX_G);
	b -= (b > MAX_B) * (b - MAX_B);
	return ((color & 0xFF000000) | (r << 16) | (g << 8) | b);
}


int	color_negative(int color)
{
	int r;
	int g;
	int b;

	r = (255 - ((color & 0x00FF0000) >> 16));
	g = (255 - ((color & 0x0000FF00) >> 8));
	b = (255 - ((color & 0x000000FF) >> 0));	
	return ((color & 0xFF000000) | (r << 16) | (g << 8) | b);
}