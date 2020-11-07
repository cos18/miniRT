/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 21:12:59 by sunpark           #+#    #+#             */
/*   Updated: 2020/11/07 16:53:58 by sunpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "minirt_struct.h"
# include "minirt_material.h"
# include "minirt_const.h"
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <stdio.h>

void			throw_error(char *message);
void			throw_error_num(char *message, int pnum);
void			*malloc_safe(size_t size);

int				get_color_val(t_vec *color);
int				get_color_sample(t_vec *color);
int				get_t(int trgb);
t_vec			*get_color(int trgb);

void			mlx_show(t_rt *rt);

int				free_strs(char **sep, int is_vaild_p, int word_locate);
char			**split_space(char const *s);

int				ft_atoi_strict(char *str);
double			ft_atod_strict(char *str);
t_vec			*vec_atod(char *str);
t_vec			*vec_atoi(char *str);

int				check_info_cnt(char **words, int len);
void			parse_resolution(t_rt *rt, char **words);
void			parse_amb_light(t_rt *rt, char **words);
void			parse_camera(t_rt *rt, char **words);
void			parse_light(t_rt *rt, char **words);

void			parse_sphere(t_rt *rt, char **words);
void			parse_plane(t_rt *rt, char **words);
void			parse_cylinder(t_rt *rt, char **words);
void			parse_triangle(t_rt *rt, char **words);
void			parse_square(t_rt *rt, char **words);

t_rt			*parse_file(char *filename, int is_mlx);
void			free_rt(t_rt *rt);

# define BMP_HEADER_SIZE 122

void			save_bmp(t_img_data *data, char	*filename);

double			clamp(double x, double min, double max);
double			get_radian(double degree);

void			draw_hittable(t_camera *cam, t_rt *rt);

typedef struct	s_sphere
{
	t_vec		*center;
	double		radius;
}				t_sphere;

t_sphere		*sphere_new(t_vec *center, double radius);
void			free_sphere(t_sphere *s);
int				sphere_hit(void *s, t_ray *r, t_hitlst_info *info,
							t_hit_record *rec);

typedef struct	s_plane
{
	t_vec		*dot;
	t_vec		*normal;
}				t_plane;

t_plane			*plane_new(t_vec *dot, t_vec *normal);
void			free_plane(t_plane *p);
int				is_in_plane(t_vec *p_dot, t_vec *p_normal, t_vec *point);
double			get_plane_ray_t(t_vec *p_dot, t_vec *p_normal, t_ray *r);
int				plane_hit(void *plane, t_ray *r, t_hitlst_info *info,
							t_hit_record *rec);

typedef struct	s_cylinder
{
	t_ray		*start;
	double		radius;
	t_vec		*end_p;
}				t_cylinder;

t_cylinder		*cylinder_new(t_vec *start_vec, t_vec *normal,
								double radius, double height);
void			free_cylinder(t_cylinder *cy);
int				cylinder_hit(void *cylinder, t_ray *r, t_hitlst_info *info,
								t_hit_record *rec);

typedef struct	s_triangle
{
	t_vec		*a;
	t_vec		*b;
	t_vec		*c;
	t_vec		*side_a;
	t_vec		*side_b;
	t_vec		*side_c;
	t_vec		*normal;
}				t_triangle;

t_triangle		*triangle_new(t_vec *a, t_vec *b, t_vec *c);
void			free_triangle(t_triangle *tr);
int				triangle_hit(void *triangle, t_ray *r, t_hitlst_info *info,
								t_hit_record *rec);

typedef struct	s_square
{
	t_vec		*normal;
	t_vec		*a;
	t_vec		*b;
	t_vec		*c;
	t_vec		*d;
	double		h_side;
}				t_square;

t_square		*square_new(t_vec *c, t_vec *normal, double side);
void			free_square(t_square *sq);
int				square_hit(void *square, t_ray *r, t_hitlst_info *info,
								t_hit_record *rec);
#endif
