/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:16:02 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/14 11:41:38 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		color_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		color_get_t(int trgb)
{
	return ((trgb & (0xFF << 24)) >> 24);
}

int		color_get_r(int trgb)
{
	return ((trgb & (0xFF << 16)) >> 16);
}

int		color_get_g(int trgb)
{
	return ((trgb & (0xFF << 8)) >> 8);
}

int		color_get_b(int trgb)
{
	return (trgb & 0xFF);
}

int		color_make_darker(double perc, int color)
{
	int t = color_get_t(color);
	int r = color_get_r(color);
	int g = color_get_g(color);
	int b = color_get_b(color);
	
	r -= perc * r;
	g -= perc * g;
	b -= perc * b; 
	if (r < 40)
		r = 40;	
	if (g < 40)
		g = 40;
	if (b < 40)
		b = 40;
	return (color_trgb(t, r, g, b));
}

int	get_opposite(int color)
{
	return (~color - 1);
}