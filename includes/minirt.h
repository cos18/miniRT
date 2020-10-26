/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunpark <sunpark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 21:12:59 by sunpark           #+#    #+#             */
/*   Updated: 2020/10/26 22:07:36 by sunpark          ###   ########.fr       */
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

int				get_color_val(t_vec *color);
int				get_t(int trgb);
t_vec			*get_color(int trgb);

t_img_data		*create_img_data(int width, int height);
void			free_img_data(t_img_data *data);

void			mlx_draw_by_img_data(t_mlx_data *mlx_data, t_img_data *img_data);
int				mlx_key_handle(int keycode);
void			mlx_show(t_img_data *data, char *title);

# define BMP_HEADER_SIZE 122
void			save_bmp(t_img_data *data, char	*filename);

double			clamp(double x, double min, double max);
double			get_radian(double degree);

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
int				plane_hit(void *plane, t_ray *r, t_hitlst_info *info,
							t_hit_record *rec);

#endif
