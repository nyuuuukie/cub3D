/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 15:57:35 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/02 09:03:09 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi_u(char *s, int *number)
{
	int i;

	i = 0;
	*number = 0;
	while (ft_isdigit(s[i]) && i < R_MAX_LEN)
	{
		*number = *number * 10 + (s[i++] - '0');
	}
	return (i);
}

void	get_number(t_map *map, char *separators, int *number)
{
	int res;

	if (map->line[map->tr.i] == '0' && ft_isdigit(map->line[map->tr.i + 1]))
		throw_parse_error(ERR_ZERO_BEFORE_NUM, &map->line[map->tr.i]);
	res = ft_atoi_u(&map->line[map->tr.i], number);
	map->tr.i += res;
	while (ft_isdigit(map->line[map->tr.i]))
		map->tr.i++;
	if (res == 0 || !ft_strchr(separators, map->line[map->tr.i]))
		throw_parse_error(ERR_MISSING_SYMBOL, &map->line[map->tr.i]);
}
