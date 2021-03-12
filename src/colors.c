/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:16:02 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/12 01:16:12 by mhufflep         ###   ########.fr       */
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
	return (trgb & (0xFF << 16));
}

int		color_get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

int		color_get_b(int trgb)
{
	return (trgb & 0xFF);
}

int		color_add_shade(double dist, int color)
{
	if (dist < 0) dist = 0;
	if (dist > 1) dist = 1;
	return ((color & 0x00FFFFFF) | ((int)((1 - dist) * 0xFF) << 24));
}

int	get_opposite(int color)
{
	return (~color - 1);
}
