/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 17:33:17 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/01 06:03:50 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	get_radian(double angle)
{
	return (angle * M_PI / 180);
}

double	get_angle(double radian)
{
	return (radian * 180 / M_PI);
}
