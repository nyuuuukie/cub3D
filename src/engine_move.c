/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:37:15 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/03 15:55:06 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_all *all, int sign, double angle)
{
	v_dbl_rotate(&all->dir, sign * angle);
	v_dbl_rotate(&all->plane, sign * angle);
}

void	move(t_all *all, t_v_dbl *base, int sign)
{
	t_v_dbl	new;

	new.x = all->pos.x + (sign * base->x * all->m_speed * all->k_speed);
	new.y = all->pos.y + (sign * base->y * all->m_speed * all->k_speed);
	if (!ft_strchr("321", all->map->arr[(int)new.x][(int)all->pos.y]))
		all->pos.x = new.x;
	if (!ft_strchr("321", all->map->arr[(int)all->pos.x][(int)new.y]))
		all->pos.y = new.y;
	if (all->map->bonus)
		move_bonus_check(all, new);
}
