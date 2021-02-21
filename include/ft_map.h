/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 06:02:52 by mhufflep          #+#    #+#             */
/*   Updated: 2021/02/21 02:29:40 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MAP_H
# define FT_MAP_H

typedef struct	s_clr
{
	int			val[3];
	int			set;
}				t_clr;

typedef struct	s_track
{
	int			line;
	int			i;
}				t_track;

typedef struct		s_map
{
	int 			r_width;
	int 			r_height;
	char			*NO_path;
	char			*SO_path;
	char			*WE_path;
	char			*EA_path;
	char			*sprite;
	t_clr			f;
	t_clr			c;
	
	int				rows;
	int				cols;
	int				f_set;
	int				c_set;
	char			**arr;
	t_list			*lst;
	char			*line;
	int				fd;
	t_track			tr;
}					t_map;

#endif