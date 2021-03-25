/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 06:02:52 by mhufflep          #+#    #+#             */
/*   Updated: 2021/03/25 19:24:06 by mhufflep         ###   ########.fr       */
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
	char			*WP_path;
	char			*FT_path;
	char			*SK_path;
	char			*AS_path;
	char			*music;
	char			*sound;
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
	char			bonus;
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

typedef struct s_sprite
{
	char id;
	t_vector p;
}				t_sprite;

typedef struct 	s_keys
{
	char w;
	char s;
	char a;
	char d;
	char r;
	char l;
	char k0;
	char k1;
	char p;
	char sh;
	char sp;
}				t_keys;

typedef struct	s_all
{
	int		screen;
	void    *mlx;
	void    *win;

	t_keys	keys;
	t_map	*map;
	t_img	img;
	
	t_texture s1;
	t_texture s2;
	t_texture no;
	t_texture so;
	t_texture we;
	t_texture ea;
	t_texture sky;
	t_texture flr;
	t_texture wpn;
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
	
	t_vector floor;

	t_sprite *sprites;
	// t_vector *sprites;
	
	t_v_int grid;
	t_v_int tex;
	
	t_v_int tex_f;
	t_v_int tex_c;
	
	double r;
	double n;
	double inc;

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
	unsigned int frame_count;
	double *ZBuffer;

	

	int offset;

	int		cmx;
	int		cmy;
	int		pmx;
	int		pmy;
	double	rotate;



	int screen_w;
	int screen_h;
	

	/* music */
	int started;
	pid_t music;
	pid_t sound;
	pthread_t pmusic;


	/* sprites */
	t_v_int scale;
	double vmove;
	t_vector t;
	t_vector d;
	t_v_int s_size;
	t_v_int s_beg;
	t_v_int s_end;

	int sp_scr_x;
	int vm_scr;	

	int	sky_exist;
	int	ceil_exist;
	int	floor_exist;
	
}				t_all;

#endif