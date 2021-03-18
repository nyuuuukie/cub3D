/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 06:02:52 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/19 00:01:11 by mhufflep         ###   ########.fr       */
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
	int				sprites;
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
	double dist;
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
	char p;
	char sh;
}				t_keys;

typedef struct	s_all
{
	int		screen;
	void    *mlx;
	void    *win;

	t_keys	keys;
	t_map	*map;
	t_img	img;
	
	t_texture s;
	t_texture no;
	t_texture so;
	t_texture we;
	t_texture ea;
	t_texture sky;
	t_texture flr;
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
	
	t_vector *sprites;
	
	t_v_int grid;

	t_v_int tex;
	
	double n;

	int		wall_beg;
	int		wall_end;
	int		hit_wall;
	int		side_wall;

	int		wall_h;
	double	k_speed;
	double	m_speed;
	double	r_angle;
	double 	dist_to_wall;
	double	ratio;

	/* shadows' parabola koefficients */
	double a;
	double b;
	double c;

	double brightness;
	int opposite;
	unsigned int frame_count;
	double *ZBuffer;
	int *s_order;
}				t_all;

#endif