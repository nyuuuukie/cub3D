/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 06:02:52 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/04 06:45:32 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct		s_clr
{
	int	set;
	int	val[3];
}					t_clr;

typedef struct		s_track
{
	int	i;
	int	line;
}					t_track;

typedef struct		s_map
{
	int			fd;
	int			w;
	int			h;
	int			rows;
	int			cols;
	int			keys;
	int			sprites;
	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	char		*wp_path;
	char		*ft_path;
	char		*ct_path;
	char		*sk_path;
	char		*as_path;
	char		*tp_path;
	char		*dg_path;
	char		*nl_path;
	char		*music;
	char		*sound;
	char		*wsound;
	char		*csound;
	char		*sprite;
	char		*line;
	char		**arr;
	char		bonus;
	t_clr		f;
	t_clr		c;
	t_list		*lst;
	t_track		tr;
}					t_map;

typedef struct		s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		len;
	int		end;
}					t_img;

typedef struct		s_v_dbl
{
	double	x;
	double	y;
	double	dist;
}					t_v_dbl;

typedef struct		s_v_int
{
	int	x;
	int	y;
}					t_v_int;

typedef struct		s_texture
{
	int		w;
	int		h;
	t_img	img;
	char	*path;
}					t_texture;

typedef struct		s_sprite
{
	char	id;
	t_v_dbl	p;
}					t_sprite;

typedef struct		s_keys
{
	char	w;
	char	s;
	char	a;
	char	d;
	char	r;
	char	l;
	char	p;
	char	f;
	char	k0;
	char	k1;
	char	sh;
}					t_keys;

typedef struct		s_all
{
	long long	frame_count;
	int			screen;
	void		*mlx;
	void		*win;

	t_keys		keys;
	t_map		*map;
	t_img		img;
	t_texture	s1;
	t_texture	s2;
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;
	t_texture	sky;
	t_texture	flr;
	t_texture	cl;
	t_texture	digits[10];
	t_texture	tp[ANIM_FRAMES];
	t_texture	wpn[ANIM_FRAMES];
	t_texture	*cur;

	int			color;
	int			sky_exist;
	int			ceil_exist;
	int			floor_exist;

	t_v_dbl		pos;
	t_v_dbl		dir;
	t_v_dbl		ray;
	t_v_dbl		cam;
	t_v_dbl		norm;
	t_v_dbl		next;
	t_v_dbl		step;
	t_v_dbl		plane;
	t_v_dbl		delta;
	t_v_dbl		floor;
	t_v_int		it;
	t_v_int		tex;
	t_v_int		grid;
	t_v_int		tex_f;
	t_v_int		tex_c;
	t_sprite	*sprites;
	t_texture	*s;
	double		r;
	double		n;
	double		inc;
	double		ratio;
	int			wall_h;
	int			wall_beg;
	int			wall_end;
	int			hit_wall;
	int			side_wall;
	double		dist_to_wall;

	int			tpf;
	int			wp_i;
	double		k_speed;
	double		m_speed;
	double		r_angle;

	double		a;
	double		b;
	double		c;

	double		rotate;
	int			cmx;
	int			cmy;
	int			pmx;
	int			pmy;
	int			screen_w;
	int			screen_h;

	pthread_t	pmusic;
	pid_t		music;
	pid_t		sound;
	pid_t		csound;
	pid_t		wsound;
	int			music_started;
	int			sound_started;
	int			wsound_started;
	int			csound_started;

	double		det;
	double		*zbuf;
	double		vmove;
	t_v_dbl		t;
	t_v_dbl		d;
	t_v_int		s_beg;
	t_v_int		s_end;
	t_v_int		scale;
	t_v_int		s_size;
	int			sp_scr_x;
	int			vm_scr;
	int			remove;
	int			kill_counter;

	t_v_dbl		f_w;
	t_v_dbl		k;
	int			num_scale;
	int			exit;
	int			debug;
}					t_all;
#endif
