/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 06:02:52 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/07 16:54:38 by mhufflep         ###   ########.fr       */
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


typedef struct  s_data
{
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct	s_plr
{
	float		x;
	float		y;
	float		dir;
	float		start;
	float		end;
}				  t_plr;


typedef struct s_vector
{
	double x;
	double y;
}				t_vector;

typedef struct s_texture
{
    int     w;
    int     h;
    void    *img;
    char    *path;
}				t_texture;


typedef struct	s_all
{
	void    *mlx;
	void    *mlx_win;
	t_data	*img;
	t_map	*map;
	t_plr	*plr;
	t_texture no;
	t_texture so;
	t_texture we;
	t_texture ea;
	int		scale;
	int		padding;
	
	t_vector pos;
	t_vector dir;
	t_vector plane;

	// double time;
	// double oldTime;

	int 	isEnabled;
	double moveSpeed;
	double rotSpeed;
}				t_all;

#endif