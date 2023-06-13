/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhufflep <mhufflep@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/02 08:59:58 by mhufflep          #+#    #+#             */
/*   Updated: 2021/04/06 01:40:37 by mhufflep         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# define _USE_MATH_DEFINES

# include <signal.h>
# include <sys/wait.h>
# include <pthread.h>

# include "mlx.h"
# include "libft.h"
# include "error.h"
# include "events.h"
# include "keycodes.h"
# include "settings.h"
# include "structures.h"
# include "bool.h"
# include "music.h"
# include "bass.h"

/*
**Engine.c
*/
int		start_engine(t_map *map, int mode);
int		stop_engine(void *ptr);

/*
**Check input arguments
*/
int		check_save_arg(int argc, char **argv);
int		check_extension(t_map *map, const char *ext);
int		check_file_path(t_map *map, char *ext);

/*
**Check scene file
*/
void	parse_scene_file(t_map *prm, char *path);
int		parse_prm(t_map *map);
int		parse_map(t_map *map);
void	parse_resolution(t_map *map);
void	parse_color(t_map *map, t_clr *clr, char *name);
void	parse_path(t_map *map, char **texture, char *name, char *ext);
void	parse_wpath(t_map *map, char **texture, char *name, char *ext);
void	parse_identify_line(t_map *map);
void	parse_identify_line_bonus(t_map *map);
int		is_prm_complete(t_map *map);
int		is_prm_complete_bonus(t_map *map);

int		map_to_list(t_map *map);
int		map_getline(t_map *map);
void	map_validate(t_map *map);
void	map_add_node(t_list **head, char *line);

void	check_portal(t_map *map);
void	check_number(int num, int min, int max);
void	check_duplicate(char *texture, char *ptr);
void	check_anim_dir(t_map *map);
void	check_symbol(t_map *map, const char c);
void	check_and_skip(t_map *map, const char c);
void	skip_symbol(t_map *map, char c);
void	skip_empty_lines(t_map *map);

int		ft_atoi_u(char *s, int *number);
void	get_number(t_map *map, char *separators, int *number);
void	print_status(char *title, char *name, char *status);
/*
**Errors.c
*/
char	*get_error_msg(t_error code);
void	throw_parse_error(t_error msg, char *add);
void	throw_engine_error(t_all *all, t_error msg, char *add);
void	print_error(char *msg, t_track *track, char *add);

/*
**Get_next_line
*/
int		get_next_line(int fd, char **line);

/*
**Arrays
*/
void	arr_delete(char **arr);
void	arr_fill(char **arr, t_list *lst);
void	arr_create(char ***arr, int rows, int cols);
int		arr_replace(char **arr, char to_replace, char replacer);

/*
**Map
*/
void	set_defaults(t_map *map);
t_map	*get_map(t_map *map);

/*
**Flood fill
*/
int		flood_fill(char **arr, int x, int y);
void	flood_fill_iter(char **arr, int x, int y);
void	player_check(int count, int row, int col);

/*
**Raycasting
*/
void	start_main_loop(t_all *all);
int		render(t_all *all);
void	fire(t_all *all);

/*
**Init
*/
void	get_screen_size(t_all *all);
void	init_all(t_all *all);
void	init_mouse(t_all *all);
void	init_coord(t_all *all);
void	init_images(t_all *all);
void	init_window(t_all *all);
void	init_textures(t_all *all);
void	init_screen_size(t_all *all);
void	init_img(t_all *all, t_img *img);
void	init_vectors(t_all *all, int i, int j);
void	init_texture(t_all *all, char *path, t_texture *t);
void	init_sprites(t_all *all);
void	init_bonus_flags(t_all *all);
void	init_shadow_params(t_all *all);
void    init_sound(t_all *all);

/*
**Vector
*/
void	v_int_init(t_v_int *vect, int x, int y);
double	v_dbl_len(t_v_dbl *v);
double	v_dbl_mlp(t_v_dbl *v1, t_v_dbl *v2);
double	v_dbl_angle(t_v_dbl *v1, t_v_dbl *v2);
void	v_dbl_rotate(t_v_dbl *v, double angle);
void	v_dbl_init(t_v_dbl *vect, double x, double y);

/*
**Key_action
*/
void	init_keys(t_all	*all);
int		key_action(t_all *all);
int		key_release(int keycode, t_all *all);
int		key_press(int keycode, t_all *all);

/*
**Engine_move.c
*/
void	rotate(t_all *all, int sign, double angle);
void	move(t_all *all, t_v_dbl *base, int sign);

/*
**Colors
*/
int		color_make_lighter(double perc, int color);
int		color_make_darker(double perc, int color);
int		color_from_txt(t_texture *txt, int x, int y);
int		color_negative(int color);
int		color_from_prm(t_clr *clr);

void	get_fc_color(t_all *all, int *f, int *c);
void	get_shadow_color(t_all *all, int *f, int *c);
void	get_lightning_color(t_all *all, int *f, int *c);
int		calculate_floor_color(t_all *all);
int		calculate_skybox_color(t_all *all);

/*
**Angle_radian.c
*/
double	get_radian(double angle);
double	get_angle(double radian);

/*
**Save
*/
void	make_screenshot(t_all *all);
void	bitmap_header(t_all *all, int fd);
void	bitmap_info_header(t_all *all, int fd);
char	*bitmap_check_exist(void);

/*
**Music
*/

/*
**Free
*/
void	free_all(t_all *all);
void	free_map(t_map *map);
void	change_pos(t_all *all, char t);
// void	kill_music(t_all *all);
/*
**Sprites
*/
void	remove_sprite(t_all *all, int x, int y);
void	sort_sprites(t_all *all);
void	calculate_weapon_offset(t_all *all);
void	calculate_dist_to_sprites(t_all *all);
void	calculate_wall_height(t_all *all);
void	calculate_wall_borders(t_all *all);
void	calculate_initial_dist(t_all *all);
void	calculate_distance_to_wall(t_all *all);
void	calculate_texture_coordinates(t_all *all);
void	calculate_collision_coordinates(t_all *all);
void	calculate_wall_prm(t_all *all, t_v_dbl *floor_wall, t_v_dbl *k);
void	check_if_sprite_hit(t_all *all, int x, int y);
void	check_shooted_sprite(t_all *all);

/*
**Mouse
*/
int		mouse_action(t_all *all);
void	move_mouse(t_all *all, int w, int h);
void	get_mouse_pos(t_all *all);

/*
**Utils.c
*/
void	swap_d_values(double *a, double *b);
void	swap_c_values(char *a, char *b);
int		random_number(int min, int max);
int		is_lightning(t_all *all);

/*
**Draw
*/
void	recognize_texture(t_all *all);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_all(t_all *all);
void	draw_hud(t_all *all);
void	draw_rain(t_all *all);
void	draw_walls(t_all *all);
void	draw_weapon(t_all *all);
void	draw_sprites(t_all *all);
void	draw_wall_line(t_all *all);
void	draw_background(t_all *all);
void	draw_floor_ceil(t_all *all);
void	draw_bonus_part(t_all *all);
void	draw_extra_data(t_all *all);
void	draw_number(t_all *all, int x, int y, int num);

void	change_pos(t_all *all, char t);
void	move_bonus_check(t_all *all, t_v_dbl n);
void	check_map_position(t_all *all, int x, int y);
void	next_level(t_all *all);

#endif
