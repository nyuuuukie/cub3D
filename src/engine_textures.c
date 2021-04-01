/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 22:59:16 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 22:59:30 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	recognize_texture(t_all *all)
{
	double ang;
	
	ang = v_dbl_angle(&all->norm, &all->ray);
	ang = get_angle(ang);

	if (all->ray.x < 0.0f)
		ang = 360 - ang;
	if (all->side_wall == 0)
	{
		if (ang >= 180.0f && ang <= 360.0f)
			all->cur = &all->no;
		else
			all->cur = &all->so;
	}	
	else
	{
		if (ang >= 90.0f && ang <= 270.0f)
			all->cur = &all->we;
		else
			all->cur = &all->ea;
	}
	all->n = ang;
}