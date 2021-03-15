/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 06:02:52 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/15 02:49:53 by mhufflep         ###   ########.fr       */
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
	int				fd;
	int 			w;
	int 			h;
	char			*NO_path;
	char			*SO_path;
	char			*WE_path;
	char			*EA_path;
	char			*sprite;
	t_clr			f;
	t_clr			c;
	char			*line;
	int				rows;
	int				cols;
	char			**arr;
	t_list			*lst;
	t_track			tr;
}					t_map;

typedef struct  s_img
{
    void        *img;
    char        *addr;
    int         bpp;
    int         len;
    int         end;
}               t_img;

typedef struct s_vector
{
	double x;
	double y;
}				t_vector;

typedef struct s_v_int
{
	int x;
	int y;
}				t_v_int;

typedef struct s_texture
{
    int     w;
    int     h;
    t_img	img;
	char    *path;
}				t_texture;

typedef struct 	s_keys
{
	char w;
	char s;
	char a;
	char d;
	char r;
	char l;
}				t_keys;

typedef struct	s_all
{
	int		screen;
	void    *mlx;
	void    *win;

	t_keys	keys;
	t_map	*map;
	t_img	img;
	
	t_texture no;
	t_texture so;
	t_texture we;
	t_texture ea;
	t_texture sky;
	t_texture *cur;
	int		color;
	
	
	/*raycast*/
	t_vector pos;
	t_vector dir;
	t_vector plane;
	t_vector norm;
	t_vector ray;
	
	t_vector next;
	t_vector delta;
	t_vector step;
	t_vector cam;
	
	t_v_int grid;

	t_v_int tex;
	
	int		wall_beg;
	int		wall_end;
	int		hit_wall;
	int		side_wall;

	int		wall_h;
	double	m_speed;
	double	r_angle;
	double 	dist_to_wall;

	/* shadows' parabola koefficients */
	double a;
	double b;
	double c;
}				t_all;

#endif